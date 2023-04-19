class ListaSequencial:
    def __init__(self, tamanho):
        self.lista = [None] * tamanho
        self.tamanho = tamanho
        self.quantidade = 0

    def __str__(self):
        return str(self.lista[:self.quantidade])

    def inserir(self, valor):
        if self.quantidade == self.tamanho:
            return False
        self.lista[self.quantidade] = valor
        self.quantidade += 1
        return True

    def remover(self, valor):
        if valor not in self.lista:
            return False
        indice = self.lista.index(valor)
        self.lista[indice] = self.lista[self.quantidade - 1]
        self.lista[self.quantidade - 1] = None
        self.quantidade -= 1
        return True

    def remover_por_posicao(self, posicao):
        if posicao < 1 or posicao > self.quantidade:
            return False
        indice = posicao - 1
        self.lista[indice] = self.lista[self.quantidade - 1]
        self.lista[self.quantidade - 1] = None
        self.quantidade -= 1
        return True

    def consultar_por_valor(self, valor):
        return valor in self.lista

    def consultar_por_posicao(self, posicao):
        if posicao < 1 or posicao > self.quantidade:
            return None
        indice = posicao - 1
        return self.lista[indice]
