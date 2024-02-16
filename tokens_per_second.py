import time

def get_tokens():
    # Your function to get tokens from the API
    pass

start_time = time.time()
token_count = 0

while True:
    token = get_tokens()
    if token is not None:
        token_count += 1

    elapsed_time = time.time() - start_time
    if elapsed_time > 0:
        tokens_per_second = token_count / elapsed_time
        print(f"Tokens per second: {tokens_per_second}")
