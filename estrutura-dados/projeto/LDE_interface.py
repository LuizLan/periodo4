from LDE import LDE
import tkinter.messagebox as messagebox
import tkinter as tk


elemento = 0 
lista = LDE()
def tela3():
    global lista
    
    def inserir_LDE():
        global elemento
        valor = int(caixa1.get())
        posicao = int(caixa2.get())
        if lista.insere(posicao, valor):
            print("Inserido com sucesso - ", lista.insere(posicao,valor))
            label_lista.config(text=str(lista))
            caixa1.delete(0, tk.END)
            caixa2.delete(0, tk.END)
            elemento=elemento+1
        else:
            print("Erro ao inserir - ", lista.insere(posicao,valor))
            messagebox.showerror("Erro", "Erro ao inserir")

    def remover_LDE():
        global elemento
        posicao = int(caixa2.get())
        if posicao > elemento:
            print("Não existe na lista")
            messagebox.showerror("Erro", "Nessa posição não há valor")
            caixa2.delete(0, tk.END)
        elif lista.remove(posicao) > 0:
            print("Removido com sucesso - ", lista.remove(posicao))
            label_lista.config(text=str(lista))
            caixa2.delete(0, tk.END)
            elemento=elemento-1
        else:
            print("Erro ao remover - ", lista.remove(posicao))
            messagebox.showerror("Erro", "Erro ao remover")
    
    def busca_valor_LDE():
        global elemento
        posicao = int(caixa2.get())

        if posicao > elemento:
            print("Não existe na lista")
            messagebox.showerror("Erro", "Não existe essa posição na lista")
        elif lista.elemento(posicao) > 0:
            print("Busca feita com sucesso, o valor é: ", lista.elemento(posicao))
        else:
            print("Erro ao buscar")
            messagebox.showerror("Erro", "Erro ao buscar")
        caixa2.delete(0, tk.END)

    def busca_posicao_LDE():
        global elemento
        valor = int(caixa1.get())

        if valor > elemento:
            print("Não existe na lista")
            messagebox.showerror("Erro", "Não existe esse valor na lista")
        elif lista.posicao(valor) > 0:
            print("Busca feita com sucesso, a posicao é: ", lista.posicao(valor))
        else:
            print("Erro ao buscar")
            messagebox.showerror("Erro", "Erro ao buscar")
        caixa1.delete(0, tk.END)

    
    label.config(text="LDE")
    # Removendo os widgets da tela anterior, se existirem
    for widget in root.winfo_children():
        if widget != label:
            widget.destroy()
    linha = tk.Frame(root, width=720, height=1, bg='black')
    linha.place(x=0, y=240)

    label_lista = tk.Label(root, text=str(lista))
    label_lista.pack(pady=200)

    botoes_iniciais()

    # Criando as caixas de texto
    caixa1 = tk.Entry(root)
    caixa1.place(x=150, y=43)
    label_caixa1 = tk.Label(root, text="Insira o valor:")
    label_caixa1.place(x=150, y=20)

    caixa2 = tk.Entry(root)
    caixa2.place(x=150, y=86)
    label_caixa2 = tk.Label(root, text="Insira a posição:")
    label_caixa2.place(x=150, y=63)

    # Criando os botões
    botao1 = tk.Button(root, text="Inserir", command=inserir_LDE, width = 12)
    botao1.place(x=350, y=43)
    botao2 = tk.Button(root, text="Remover", command=remover_LDE, width = 12)
    botao2.place(x=450, y=43)
    botao3 = tk.Button(root, text="Busca Posição", command=busca_posicao_LDE, width = 12)
    botao3.place(x=350, y=80)
    botao4 = tk.Button(root, text="Busca Valor", command=busca_valor_LDE, width = 12)
    botao4.place(x=450, y=80)
    
root = tk.Tk()
root.geometry("720x480")
root.title("Projeto Estrutura de Dados")

# Label para exibir a tela atual
label = tk.Label(root, text="Tela Inicial")
label.pack()

def botoes_iniciais():
    # # Botão para trocar para tela 1
    # botao1 = tk.Button(root, text="Lista Sequencial", command=print("ops"), width = 12)
    # botao1.place(x=0, y=26)

    # # Botão para trocar para tela 2
    # botao2 = tk.Button(root, text="LSE", command=print("ops"), width = 12)
    # botao2.place(x=0, y=53)

    # Botão para trocar para tela 3
    botao3 = tk.Button(root, text="LDE", command=tela3, width = 12)
    botao3.place(x=0, y=79)

botoes_iniciais()

root.mainloop()