# 弹幕机 API 版
# 每隔一定时间向直播间 API 请求一次数据，获取最近的 10 条弹幕
# 根据两次获取间的新弹幕数调整请求间隔，存在滞后性，且无法应对弹幕更新非常快的情况

import requests
import json
from time import sleep

room_id = '795746' # 直播间序号
url = 'https://api.live.bilibili.com/xlive/web-room/v1/dM/gethistory?roomid=' + room_id # API
last_li = json.loads(requests.get(url).text)["data"]["room"] # 获取初始弹幕列表
while True:
	result = requests.get(url).text
	lis = json.loads(result)["data"]["room"] # 获取弹幕列表

	# 计算新弹幕数
	diff = 0 # 本次获取的新弹幕数
	while lis[0]["text"] != last_li[diff]["text"]: # 若不相等
		diff += 1
		if diff == 10:
			break

	# 打印弹幕
	count = 9 # 弹幕序号 (弹幕从最老的开始打印)
	for entry in lis:
		print(str(count)+'# '+entry["nickname"]+'\n'+entry["text"])
		count -= 1

	# 后处理
	last_li = lis # 暂存本次弹幕
	print() # 空行
	sleep_time = 9 - 0.8 * diff # 根据新弹幕数调整请求间隔 [1, 9]
	sleep(sleep_time) # 实现请求间隔