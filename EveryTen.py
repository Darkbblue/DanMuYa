# 弹幕机 API 版
# 每隔一定时间向直播间 API 请求一次数据，获取最近的 10 条弹幕
# 根据两次获取间的新弹幕数调整请求间隔，存在滞后性，且无法应对弹幕更新非常快的情况

# 增量更新模式：每次只显示新增弹幕，无新增弹幕时无操作

import requests
import json
from time import sleep

def print_list(lis):
	# 打印弹幕列表，传入参数是列表和需要打印的数目
	count = len(lis) - 1
	for entry in lis: # 截取新弹幕部分
		print(str(count)+'# '+entry["nickname"]+'\n'+entry["text"])
		count -= 1
	print() # 空行

if __name__ == '__main__':
	room_id = '508109' # 直播间序号
	url = 'https://api.live.bilibili.com/xlive/web-room/v1/dM/gethistory?roomid=' + room_id # API
	last_li = json.loads(requests.get(url).text)["data"]["room"] # 获取初始弹幕列表
	print_list(last_li) # 打印初始弹幕

	while True: # 工作循环
		result = requests.get(url).text
		lis = json.loads(result)["data"]["room"] # 获取弹幕列表

		# 计算新弹幕数
		diff = 0 # 本次获取的新弹幕数
		while lis[0]["text"] != last_li[diff]["text"]: # 若不相等
			diff += 1
			if diff == 10:
				break

		# 有新弹幕时进行
		if diff:
			# 打印弹幕
			print_list(lis[10 - diff: ]) # 仅打印更新部分
			# 后处理
			last_li = lis # 暂存本次弹幕

		sleep_time = 9 - 0.8 * diff # 根据新弹幕数调整请求间隔 [1, 9]
		sleep(sleep_time) # 实现请求间隔