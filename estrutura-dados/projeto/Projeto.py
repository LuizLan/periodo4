from tkinter import *
from LSE import LSE

import tkinter.messagebox as messagebox
import tkinter as tk



def tela1():
    label.config(text="Lista Sequencial")
    # Removendo os widgets da tela anterior, se existirem
    for widget in root.winfo_children():
        if widget != label:
            widget.destroy()

    # Dividindo a tela em duas partes iguais com uma linha
    linha = tk.Frame(root, width=720, height=1, bg='black')
    linha.place(x=0, y=240)

    botoes_iniciais()

    # Criando as caixas de texto
    caixa1 = tk.Entry(root)
    caixa1.place(x=300, y=43)
    label_caixa1 = tk.Label(root, text="Insira o valor:")
    label_caixa1.place(x=300, y=20)

    caixa2 = tk.Entry(root)
    caixa2.place(x=300, y=86)
    label_caixa2 = tk.Label(root, text="Insira a posição:")
    label_caixa2.place(x=300, y=63)

    # Criando os botões
    botao1 = tk.Button(root, text="Inserir", command=lambda: print("Botão 1 clicado"), width = 12)
    botao1.place(x=550, y=43)
    botao2 = tk.Button(root, text="Remover", command=lambda: print("Botão 2 clicado"), width = 12)
    botao2.place(x=850, y=43)
    botao3 = tk.Button(root, text="Busca Posição", command=lambda: print("Botão 3 clicado"), width = 12)
    botao3.place(x=550, y=80)
    botao4 = tk.Button(root, text="Busca Valor", command=lambda: print("Botão 4 clicado"), width = 12)
    botao4.place(x=850, y=80)

def tela2():

    lista = LSE()

    ######################## FUNCOES ###################

    def inserir():
        valor = int(caixa1.get())
        posicao = int(caixa2.get())
        if lista.insere(posicao, valor):
            print("Inserido com sucesso")

        else:
            print("Erro ao inserir")
            messagebox.showerror("Erro", "Erro ao inserir")
            
        caixa1.delete(0, tk.END)
        caixa2.delete(0, tk.END)

    def remover():
        posicao = int(caixa2.get())
        if lista.remove(posicao) != -1:
            print("Removido com sucesso")
        else:
            print("Erro ao remover")
            messagebox.showerror("Erro", "Erro ao remover, posição inválida")
            
        caixa2.delete(0, tk.END)
    
    def busca_posicao():
        posicao = int(caixa2.get())

        if lista.elemento(posicao) != -1:
            print("Busca feita com sucesso, o valor é: ", lista.elemento(posicao))
            messagebox.showinfo(message=("Busca feita com sucesso, a posição é: ", lista.elemento(posicao)))        
        else:
            print("Erro ao buscar")
            messagebox.showerror("Erro", "Erro ao bucar posição")
            
        caixa2.delete(0, tk.END)

    def busca_valor():
        valor = int(caixa1.get())

        if lista.posicao(valor) != -1:
            print("Busca feita com sucesso, a posição é: ", lista.posicao(valor))
            messagebox.showinfo(message=("Busca feita com sucesso, a posição é: ", lista.posicao(valor)))
            
        else:
            print("Erro ao buscar, valor nao esta na lista ou é inválido")
            messagebox.showerror("Erro", "Erro ao bucar valor")
            
        caixa1.delete(0, tk.END)

    ######################## INTERFACE GRAFICA (GUI) ###################
    label.config(text="LSE")

    for widget in root.winfo_children():
        if widget != label:
            widget.destroy()

    botoes_iniciais()
    ######################## COMPONENTES (WIDGETS) ###################
    
    linha = tk.Frame(root, width=1080, height=1, bg='black')

    caixa1 = tk.Entry(root)
    label_caixa1 = tk.Label(root, text="Insira o valor:")

    caixa2 = tk.Entry(root)
    label_caixa2 = tk.Label(root, text="Insira a posição:")

    ## imagens ##

    #soma = PhotoImage(file="estrutura-dados\projeto\soma.png")
    #soma = soma.subsample(20, 20)
    #figura = Label(root, image=soma)
    #figura.image = soma

    #############

    botao1 = tk.Button(root, text= 'inserir', command=inserir, bd=0, highlightthickness=0)
    botao2 = tk.Button(root, text="Remover", command= remover, width = 12)
    botao3 = tk.Button(root, text="Busca Posição (informe valor)", command= busca_valor, width = 24)
    botao4 = tk.Button(root, text="Busca Valor (informe posicao)", command= busca_posicao, width = 24)
    
    visualizacao = tk.Label(root, text= "Lista: ", font=("Arial", 12))

    ######################## POSICAO DOS COMPONENTES (LAYOUT) ###################

    linha.place(x=0, y=340)

    caixa1.place(x=300, y=43)
    label_caixa1.place(x=300, y=20)

    caixa2.place(x=300, y=86)
    label_caixa2.place(x=300, y=63)

    botao1.place(x=550, y=43)
    botao2.place(x=850, y=43)
    botao3.place(x=550, y=80)
    botao4.place(x=850, y=80)

    visualizacao.place(x= 360, y=300)

def tela3():
    label.config(text="LDE")
    # Removendo os widgets da tela anterior, se existirem
    for widget in root.winfo_children():
        if widget != label:
            widget.destroy()
    linha = tk.Frame(root, width=720, height=1, bg='black')
    linha.place(x=0, y=240)

    botoes_iniciais()

root = tk.Tk()
root.geometry("1080x720")
root.title("Projeto Estrutura de Dados")

# Label para exibir a tela atual
label = tk.Label(root, text="Tela Inicial")
label.pack()

def botoes_iniciais():
    # Botão para trocar para tela 1
    botao1 = tk.Button(root, text="Lista Sequencial", command=tela1, width = 12)
    botao1.place(x=0, y=26)

    # Botão para trocar para tela 2
    botao2 = tk.Button(root, text="LSE", command=tela2, width = 12)
    botao2.place(x=0, y=53)

    # Botão para trocar para tela 3
    botao3 = tk.Button(root, text="LDE", command=tela3, width = 12)
    botao3.place(x=0, y=79)

botoes_iniciais()

root.mainloop()