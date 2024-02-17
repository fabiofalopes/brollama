import requests
import json

def make_api_request(model, prompt):
    url = "http://localhost:11434/api/generate"
    data = {
        "model": model,
        "prompt": prompt
    }

    response = requests.post(url, data=json.dumps(data), stream=True)

    text = ""
    for line in response.iter_lines():
        if line:
            decoded_line = line.decode('utf-8')
            json_line = json.loads(decoded_line)
            print(json_line['response'], end="")
            text += json_line['response']
    text += "\n\n"
    print("\n================================")
    #print("\n\nFull text:\n", text)        
    return response

# model = "orca-mini" #3B model
model = "llama2-uncensored" #7B model
prompt = ""

while True:
    prompt = input("Enter a prompt: ") 
    make_api_request(model, prompt)

