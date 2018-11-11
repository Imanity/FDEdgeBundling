class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []

    def read(self, users):
        for user in users:
            uid = user[0]
            username = user[1]
            if [uid, username] in self.nodes:
                continue
            self.nodes.append([uid, username])
        for user in users:
            uid1 = user[0]
            for uid2 in user[2]:
                if [uid1, uid2] in self.edges or [uid2, uid1] in self.edges:
                    continue
                self.edges.append([uid1, uid2])
    
    def save(self, path):
        node_path = path + 'nodes.txt'
        edge_path = path + 'edges.txt'

        node_file = open(node_path, 'w')
        for node in self.nodes:
            node_file.write(str(node[0]))
            node_file.write(' ')
            node_file.write(str(node[1]))
            node_file.write('\n')
        node_file.close()

        edge_file = open(edge_path, 'w')
        for edge in self.edges:
            edge_file.write(str(edge[0]))
            edge_file.write(' ')
            edge_file.write(str(edge[1]))
            edge_file.write('\n')
        edge_file.close()
