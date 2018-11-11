import queue
import json
import requests
from graph import Graph

access_token = ''
token_path = 'token.txt'
start_url = 'https://api.github.com/users/'
users_save_path = '../Data/'
avatars_path = '../Data/Avatars/'

def get_users(users, start_username, max_users):
    q = queue.Queue()
    q.put(start_url + start_username + '?access_token=' + access_token)
    while not q.empty() and len(users) < max_users:
        url = q.get()
        r = requests.get(url).json()

        if len(r) < 3:
            print(r)
            continue
        
        username = r['login']
        uid = r['id']

        avatar_url = r['avatar_url']
        get_avatar(avatar_url, uid)

        following_uids = []
        following_url = start_url + username + '/following?per_page=100&access_token=' + access_token
        following_json = requests.get(following_url).json()

        if len(following_json) < 1:
            print(following_json)
            continue

        for i in range(0, len(following_json)):
            q.put(start_url + following_json[i]['login'] + '?access_token=' + access_token)
            following_uids.append(following_json[i]['id'])
        
        print(username)
        users.append([uid, username, following_uids])

def get_avatar(url, uid):
    html = requests.get(url)
    with open(avatars_path + str(uid) + '.png', 'wb') as file:
        file.write(html.content)

if __name__ == '__main__':
    print('---  Get token.  ---')
    token_file = open(token_path, 'r')
    access_token = token_file.read().strip()
    token_file.close()
    print('  Token: ' + access_token)

    users = []
    print('---  Get users.  ---')
    get_users(users, 'Imanity', 200)
    print('  User num: ' + str(len(users)))

    print('--- Build graph. ---')
    graph = Graph()
    graph.read(users)
    graph.save(users_save_path)
    print('  Node num: ' + str(len(graph.nodes)))
