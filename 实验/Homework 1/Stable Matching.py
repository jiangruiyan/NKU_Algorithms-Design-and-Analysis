# 导入双端队列模块，用于高效处理自由男性的队列
from collections import deque

# 读取输入的男女人数
n = int(input())

# 初始化男性列表和男性偏好字典
men = []
men_prefs = {}
for _ in range(n):
    # 解析每行输入（示例格式："A:X>Y>Z"）
    line = input().strip()
    name, prefs = line.split(':')  # 拆分姓名和偏好部分
    men.append(name)  # 将男性姓名加入列表
    men_prefs[name] = prefs.split('>')  # 存储偏好列表（按顺序存储）

# 初始化女性偏好字典（存储男性排名）
women_rankings = {}
for _ in range(n):
    # 解析每行输入（示例格式："X:A>B>C"）
    line = input().strip()
    name, prefs = line.split(':')  # 拆分姓名和偏好部分
    prefs_list = prefs.split('>')  # 将偏好转为列表
    # 创建字典：键为男性名，值为对应的排名（数值越小表示越喜欢）
    women_rankings[name] = {m: idx for idx, m in enumerate(prefs_list)}

# 初始化匹配状态（所有女性初始未匹配）
current_matches = {w: None for w in women_rankings}
# 记录每个男性下一个要追求的偏好索引（初始都从第一个开始）
next_proposal = {m: 0 for m in men}
# 创建自由男性队列（初始包含所有男性）
free_men = deque(men)

# Gale-Shapley算法核心实现
while free_men:
    m = free_men.popleft()  # 取出队列最左边的自由男性
    
    # 如果该男性已经没有更多偏好女性可求婚（理论上不会发生）
    if next_proposal[m] >= len(men_prefs[m]):
        continue
    
    # 获取当前要追求的女士
    w = men_prefs[m][next_proposal[m]]
    next_proposal[m] += 1  # 不论结果如何，下次将从下一位开始
    
    if current_matches[w] is None:  # 女士当前无伴侣
        current_matches[w] = m  # 直接匹配
    else:
        current = current_matches[w]  # 获取女士当前伴侣
        # 比较当前伴侣和新追求者的排名
        if women_rankings[w][m] < women_rankings[w][current]:
            current_matches[w] = m  # 替换为更优的追求者
            free_men.append(current)  # 原伴侣重回自由队列
        else:
            free_men.append(m)  # 追求失败，重回队列等待下次机会

# 构造男性视角的匹配结果（原字典是女性视角）
male_partner = {m: w for w, m in current_matches.items()}

# 按初始顺序输出所有男性的匹配结果
for man in men:
    print(f"({man},{male_partner[man]})")