class TrieNode:
    def __init__(self):
        self.children = {}
        self.end_of_word = False

class Trie:
    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                node.children[char] = TrieNode()
            node = node.children[char]
        node.end_of_word = True

    def search(self, word):
        node = self.searchNode(word)
        return node is not None and node.end_of_word

    def searchNode(self, word):
        node = self.root
        for char in word:
            if char not in node.children:
                return None
            node = node.children[char]
        return node
    
TRIE = Trie()
def find_line(linia):
    dp = [0 for _ in range(len(linia) + 1)]
    backtrack = [-1 for _ in range(len(linia) + 1)]

    for i in range(1, len(linia) + 1):
        for j in range(i):
            word = linia[j:i]
            if TRIE.search(word) and (j == 0 or dp[j] > 0): #sprawdzam czy można dokleić to słowo i czy to w ogóle słowo
                #można dokleić to słowo, sprawdzam czy się opłaca
                if dp[i] < dp[j] + len(word):
                    dp[i] = dp[j] + len(word)
                    backtrack[i] = j
    
    #odtwarzanie listy słów
    lista_slow = []
    i = len(linia)
    while i > 0:
        j = backtrack[i]
        lista_slow.append(linia[j:i])
        i = j
    lista_slow.reverse()
    return ' '.join(lista_slow)

#początek mania
with open('words_for_ai1.txt', 'r') as plik:
    for slowo in plik:
        TRIE.insert(slowo[:-1])

ans = open('zad2_output.txt', 'w')
with open('zad2_input.txt', 'r') as plik:
    for linia in plik:
        ans.write(find_line(linia[:-1]) + " \n")

ans.close()
