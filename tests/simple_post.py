import requests

req = requests.post('http://127.0.0.1', data={
    'name': 'user',
    'password': '123456',
})

print(req.status_code, req.reason)

print(req.text)
