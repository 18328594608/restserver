import subprocess
import datetime
import time
# 定义 rsetserver 的启动命令
start_command = "./rsetserver"

# 定义日志文件路径
log_file_path = "./crash.log"

while True:
    # 启动 rsetserver 服务
    process = subprocess.Popen(start_command.split())

    # 监控服务状态
    while True:
        # 获取服务状态
        poll = process.poll()

        # 如果服务已经结束，则记录崩溃日志信息并重新启动服务
        if poll is not None:
            with open(log_file_path, "a") as f:
                f.write(f"Crash time: {datetime.datetime.now()}\n")
                f.write(f"Exit code: {poll}\n\n")
            break

        # 每隔一段时间检查一次服务状态
        time.sleep(10)
