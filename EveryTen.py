# 弹幕机 API 版
# 每隔一定时间向直播间 API 请求一次数据，获取最近的 10 条弹幕
# 根据两次获取间的新弹幕数调整请求间隔

# 增量更新模式：每次只显示新增弹幕，无新增弹幕时无操作

# 无法应对弹幕更新非常快的情况

import requests
import json
from time import sleep

# 使用前修改此处 --------------------
room_id = '1029' # 直播间序号
# 使用前修改此处 --------------------

def print_list(lis):
	# 打印弹幕列表，传入参数是待打印列表
	count = len(lis) - 1
	for entry in lis:
		print(str(count)+'# '+entry["nickname"]+'\n'+entry["text"])
		count -= 1
	print() # 空行

if __name__ == '__main__':
	url = 'https://api.live.bilibili.com/xlive/web-room/v1/dM/gethistory?roomid=' + room_id # API
	last_li = json.loads(requests.get(url).text)["data"]["room"] # 获取初始弹幕列表
	print_list(last_li) # 打印初始弹幕
	sleep_time = 5 # 初始化间隔时间
	last_diff = 0 # 初始化上次新弹幕数

	while True: # 工作循环
		result = requests.get(url).text
		lis = json.loads(result)["data"]["room"] # 获取弹幕列表

		# 计算新弹幕数
		diff = 0 # 本次获取的新弹幕数
		if lis:
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

		# 更新间隔时长，调整范围 [1, 10]
		step = diff - last_diff # 基础步长由两次新弹幕数作差得到，若弹幕增多则数值为正，对应间隔应减小

		if diff == 10: # 处理两个边界情况，确保达到边界后依然能够调整间隔
			step += 6
		elif diff == 0 and step == 0: # 有更新状态下第一次遇到无更新获取时不启用额外步长
			step -= 4

		sleep_time -= step * 0.3 # 以相对小的实际步长调整间隔
		if sleep_time > 10: # 规约越界情况
			sleep_time = 10
		elif sleep_time < 1:
			sleep_time = 1

		last_diff = diff # 记录本次新弹幕数
		sleep(sleep_time) # 实现请求间隔