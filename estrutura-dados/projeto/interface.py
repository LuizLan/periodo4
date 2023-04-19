from LSE import LSE
from tkinter import *
from tkinter import ttk
import tkinter.messagebox as messagebox

class ListaSequencial:

    def __init__(self, root):

        root.title("Lista Sequencial")

        mainframe = ttk.Frame(root, padding="3 3 12 12", height=720, width=480)
        mainframe.grid(column=0, row=0, sticky=(N, W, E, S))
        root.columnconfigure(0, weight=1)
        root.rowconfigure(0, weight=1)


'''
def __init__(self, tamanho):
    self.lista = LSE()
    self.window = Tk()
    self.window.title("Lista Sequencial")
    self.window.geometry("300x300")

    self.label = tk.Label(self.window, text=str(self.lista))
    self.label.pack(pady=10)

    self.valor_entry = tk.Entry(self.window)
    self.valor_entry.pack(pady=5)

    self.inserir_button = tk.Button(self.window, text="Inserir", command=self.inserir)
    self.inserir_button.pack(pady=5)

    self.remover_por_valor_button = tk.Button(self.window, text="Remover por valor", command=self.remover_por_valor)
    self.remover_por_valor_button.pack(pady=5)

    self.remover_por_posicao_button = tk.Button(self.window, text="Remover por posição", command=self.remover_por_posicao)
    self.remover_por_posicao_button.pack(pady=5)

    self.consultar_por_valor_button = tk.Button(self.window, text="Consultar por valor", command=self.consultar_por_valor)
    self.consultar_por_valor_button.pack(pady=5)

    self.consultar_por_posicao_button = tk.Button(self.window, text="Consultar por posição", command=self.consultar_por_posicao)
    self.consultar_por_posicao_button.pack(pady=5)

    self.window.mainloop()

def inserir(self):
    valor = int(self.valor_entry.get())
    if self.lista.inserir(valor):
        self.label.config(text=str(self.lista))
        self.valor_entry.delete(0, tk.END)
    else:
        messagebox.showerror("Erro", "A lista está cheia.")

def remover_por_valor(self):
    valor = int(self.valor_entry.get())
    if self.lista.remover(valor):
        self.label.config(text=str(self.lista))
        self.valor_entry.delete(0, tk.END)
    else:
        messagebox.showerror("Erro", f"{valor} não encontrado na lista.")

def remover_por_posicao(self):
    posicao = int(self.valor_entry.get()) - 1 # converte a posição para index (começando em 0)
    if self.lista.remover_por_posicao(posicao):
        self.label.config(text=str(self.lista))
        self.valor_entry.delete(0, tk.END)
    else:
        messagebox.showerror("Erro", "Posição inválida.")
        self.valor_entry.delete(0, tk.END)

def consultar_por_valor(self):
    valor = int(self.valor_entry.get())
    if self.lista.consultar_por_valor(valor):
        posicao = self.lista.lista.index(valor) + 1 # converte o index para posição (começando em 1)
        messagebox.showinfo("Consulta", f"{valor} está na posição {posicao}.")
        self.valor_entry.delete(0, tk.END)
    else:
        messagebox.showerror("Erro", f"{valor} não encontrado na lista.")
        self.valor_entry.delete(0, tk.END)

def consultar_por_posicao(self):
    posicao = int(self.valor_entry.get()) - 1 # converte a posição para index (começando em 0)
    valor = self.lista.consultar_por_posicao(posicao)
    if valor is not None:
        posicao = posicao + 1 # converte o index para posição (começando em 1)
'''