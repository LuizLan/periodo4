from tkinter import *

class Node:
    def __init__(self, value):
        self.value = value
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
        else:
            current_node = self.head
            while current_node.next is not None:
                current_node = current_node.next
            current_node.next = new_node
        self.display()

    def remove(self, value):
        if self.head is None:
            return
        elif self.head.value == value:
            self.head = self.head.next
        else:
            current_node = self.head
            while current_node.next is not None:
                if current_node.next.value == value:
                    current_node.next = current_node.next.next
                    break
                current_node = current_node.next
        self.display()

    def search(self, value):
        if self.head is None:
            return
        current_node = self.head
        while current_node is not None:
            if current_node.value == value:
                current_node.button.configure(bg="yellow")
            else:
                current_node.button.configure(bg="white")
            current_node = current_node.next

    def display(self):
        if self.head is None:
            return
        current_node = self.head
        x = 100
        while current_node is not None:
            current_node.button.place(x=x, y=50)
            x += 50
            current_node = current_node.next

class App:
    def __init__(self, master):
        self.master = master
        self.linked_list = LinkedList()

        self.value_entry = Entry(master, width=10)
        self.value_entry.place(x=50, y=10)

        self.insert_button = Button(master, text="Insert", command=self.insert)
        self.insert_button.place(x=160, y=8)

        self.remove_button = Button(master, text="Remove", command=self.remove)
        self.remove_button.place(x=210, y=8)

        self.search_button = Button(master, text="Search", command=self.search)
        self.search_button.place(x=260, y=8)

    def insert(self):
        value = self.value_entry.get()
        self.linked_list.insert(value)
        self.value_entry.delete(0, END)

    def remove(self):
        value = self.value_entry.get()
        self.linked_list.remove(value)
        self.value_entry.delete(0, END)

    def search(self):
        value = self.value_entry.get()
        self.linked_list.search(value)
        self.value_entry.delete(0, END)

root = Tk()
app = App(root)
root.geometry("500x100")
root.mainloop()
