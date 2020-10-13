# 弹幕机 WebSocket 版
# 建立与服务器的稳定 WebSocket 连接，即时接收任何信息
# 对接收到的弹幕、礼物等信息进行打印，其余信息不予处理

# 打印内容可自行修改，可增加本地保存等功能

import asyncio # 异步操作
from aiowebsocket.converses import AioWebSocket # WebSocket
import json
import zlib

# 使用前修改此处 --------------------
room_id = '605391' # 直播间序号
# 使用前修改此处 --------------------

# 发送心跳
async def heart_beat(sock):
	while True: # 无限循环
		await asyncio.sleep(30) # 每 30s 一次
		await sock.send(bytes.fromhex('00000010001000010000000200000001')) # 发送空包

# 接收信息
async def rcvmsg(sock):
	while True: # 无限循环
		msg = await sock.receive() # 等待信息到来
		parse_msg(msg) # 解析信息

# 解析信息
def parse_msg(msg):
	# 头部信息解析
	header_len = int(msg[0:4].hex(), 16) # 数据包长度
	header_ver = int(msg[6:8].hex(), 16) # 协议类型
	header_op = int(msg[8:12].hex(), 16) # 操作类型
#	print(str(header_len)+' '+str(header_ver)+' '+str(header_op))

	# 处理粘包
	if len(msg) > header_len:
		parse_msg(msg[ :header_len])
		parse_msg(msg[header_len: ])
		return

	body = msg[16: ] # 数据部分

	# 根据协议类型进行处理
	if header_ver == 2: # 压缩数据，解压缩后处理
		parse_msg(zlib.decompress(body))
		return
	elif header_ver == 1: # 人气值，不予处理
		return
	# else: json，可能需要进行解析

	# 根据操作类型进行处理
	if header_op == 5: # 来自服务器的各类信息
		content = json.loads(body.decode('utf-8', errors='ignore')) # 转换 json 格式
#		print(content)
		if content["cmd"] == "DANMU_MSG": # 弹幕
			print_danmu(content)
		if content["cmd"] == "SEND_GIFT": # 礼物
			print_gift(content)

# 打印弹幕
danmu_history = ['', '', ''] # 弹幕历史，只保存弹幕内容不保存用户名 (处理高能时期的群体复读)
def print_danmu(content):
	if content["info"][1] in danmu_history: # 若缓存中存在
		return # 不打印
	print('# ' + content["info"][2][1]) # 用户名
	print(content["info"][1]) # 弹幕内容
	print() # 空行
	del danmu_history[0] # 清理历史最旧一个
	danmu_history.append(content["info"][1]) # 插入

# 打印礼物
gift_history = [('', ''), ('', ''), ('', '')] # 礼物历史，格式 (uname, giftName)
def print_gift(content):
	info = (content["data"]["uname"], content["data"]["giftName"]) # 提取核心信息
	if info in gift_history: # 若缓存中存在
		return # 不打印复读机的礼物
	print('$ ------------------ $')
	print(info[0] + '  ' + info[1]) # 用户名和礼物名称
	print('$ ------------------ $')
	print() # 空行
	del gift_history[0] # 清理历史最旧一个
	gift_history.append(info) # 插入

# 初始化连接
async def startup(url):
	init_msg = '000000{len}0010000100000007000000017b22726f6f6d6964223a{room}7d' # 初始化连接要求的信息
	room_id_hex = ''.join(map(lambda x: hex(ord(x))[2: ], list(room_id))) # 直播间序号逐位转换到 ASCII 码的十六进制
	init_msg = init_msg.format(len=hex(27 + len(room_id))[2: ], room=room_id_hex) # 填充包长和直播间序号字段

	async with AioWebSocket(url) as aws: # 连接建立
		converse = aws.manipulator # socket
		await converse.send(bytes.fromhex(init_msg)) # 发送初始化信息
		print('connection established')
		tasks = [heart_beat(converse), rcvmsg(converse)] # 两个异步任务 - 发送心跳，接收信息
		await asyncio.wait(tasks)


if __name__ == '__main__':
	remote = 'wss://broadcastlv.chat.bilibili.com:2245/sub' # ws 入口
	try:
		asyncio.get_event_loop().run_until_complete(startup(remote)) # 初始化连接
	except KeyboardInterrupt as exc: # 手动退出
		print('quitting')