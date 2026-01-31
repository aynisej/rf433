import tkinter as tk
from tkinter import filedialog, messagebox, simpledialog, Listbox, Scrollbar, END
import os
import serial
import serial.tools
from serial.tools import list_ports
import time
import binascii

# ===== НАСТРОЙКИ =====
RX_PORT = None
TX_PORT = None
PORT = "/dev/serial/by-id/usb-1a86_USB_UART-LPT-if00-port0/"
BAUD = 2400
ATTEMPTS = 10
DELAY = 0.2

CAPTURE_FILE = "capture.bin"
BITS_FILE = "bits.txt"
PULSES_FILE = "pulses.txt"
FINAL_FILE = "final_code.txt"
BEST_DIR = "best_codes"


os.makedirs(BEST_DIR, exist_ok=True)


# ===== ЛОГИКА =====
def list_serial_ports():
    return [p.device for p in list_ports.comports()]
def select_rx_port():
    select_port_generic("RX")
def select_tx_port():
    select_port_generic("TX")
def select_port_generic(role):
    ports = list_serial_ports()
    if not ports:
        messagebox.showerror("ti eblan")
        return
    win = tk.Toplevel(root)
    win.title(f"viberi port {role}")

    lb = Listbox(win, width=50)
    for p in ports:
        lb.insert(END, p)

        def apply():
            global RX_PORT, TX_PORT
            idx = lb.curselection()
            if not idx:
                return
            if role == "RX":
                RX_PORT = ports[idx[0]]
            else:
                TX_PORT = ports[idx[0]]
                win.destroy()
            tk.Button( win, text="primenit", command=apply).pack(pady=5)

def select_port():
    ports = list_serial_ports()
    if not ports:
        messagebox.showerror("Ошибка", "UART устройства не найдены")
        return

    win = tk.Toplevel(root)
    win.title("Выбор порта")

    tk.Label(win, text="Доступные UART порты:").pack(pady=5)

    lb = Listbox(win, width=50)
    for p in ports:
        lb.insert(END, p)
    lb.pack(padx=10, pady=5)

    def apply():
        global PORT
        idx = lb.curselection()
        if not idx:
            return
        PORT = ports[idx[0]]
        messagebox.showinfo("Порт выбран", f"Текущий порт:\n{PORT}")
        win.destroy()

    tk.Button(win, text="Применить", command=apply).pack(pady=5)
def capture_signal():
    """Захватить сигнал в BIN"""
    duration = simpledialog.askinteger("Захват", "Длительность (сек):", minvalue=1, maxvalue=20)
    if not duration:
        return
    ser = serial.Serial(RX_PORT or PORT, BAUD, timeout=1)
    data = ser.read(duration * BAUD)
    ser.close()
    with open(CAPTURE_FILE, "wb") as f:
        f.write(data)
    messagebox.showinfo("Успех", f"Захвачено {len(data)} байт в {CAPTURE_FILE}")


def decode_signal():
    """Перевести BIN в импульсы и биты"""
    if not os.path.exists(CAPTURE_FILE):
        messagebox.showwarning("Ошибка", "Нет capture.bin")
        return

    with open(CAPTURE_FILE, "rb") as f:
        raw = f.read()

    pulses = []
    last = None
    count = 0
    for b in raw:
        val = 1 if b != 0 else 0
        if last is None:
            last = val
            count = 1
        elif val == last:
            count += 1
        else:
            pulses.append((last, count))
            last = val
            count = 1
    if count > 0:
        pulses.append((last, count))

    bits = "".join([str(val) * count for val, count in pulses])

    with open(PULSES_FILE, "w") as f:
        for p in pulses:
            f.write(str(p) + "\n")
    with open(BITS_FILE, "w") as f:
        f.write(bits)

    messagebox.showinfo("Готово", f"Импульсов: {len(pulses)}\nБитов: {len(bits)}\nСохранено в {BITS_FILE}")


def find_pattern():
    """Поиск повторяющихся кодов"""
    if not os.path.exists(BITS_FILE):
        messagebox.showwarning("Ошибка", "Нет bits.txt")
        return

    with open(BITS_FILE, "r") as f:
        bits = f.read().strip()

    found = []
    for size in range(16, 65):
        seq = bits[:size]
        repeats = bits.count(seq)
        if repeats > 1:
            found.append((seq, size, repeats))

    if not found:
        messagebox.showinfo("Результат", "Повторов не найдено")
        return

    seq, size, repeats = found[0]  # первый подходящий
    with open(FINAL_FILE, "w") as f:
        f.write(seq)

    messagebox.showinfo("Найден код", f"Длина: {size}\nПовторов: {repeats}\nСохранено в {FINAL_FILE}")


def save_best():
    """Сохранить код с уникальным именем"""
    if not os.path.exists(FINAL_FILE):
        messagebox.showwarning("Ошибка", "Нет final_code.txt")
        return

    with open(FINAL_FILE, "r") as f:
        bits = f.read().strip()

    name = simpledialog.askstring("Сохранение", "Имя кода (например vorota):")
    if not name:
        return
    path = os.path.join(BEST_DIR, f"{name}.txt")
    with open(path, "w") as f:
        f.write(bits)

    messagebox.showinfo("Успех", f"Код сохранён в {path}")


def list_codes():
    """Показать сохранённые коды"""
    files = [f for f in os.listdir(BEST_DIR) if f.endswith(".txt")]
    if not files:
        messagebox.showwarning("Нет кодов", "Каталог пуст")
        return

    win = tk.Toplevel(root)
    win.title("Сохранённые коды")

    scrollbar = Scrollbar(win)
    scrollbar.pack(side=tk.RIGHT, fill=tk.Y)

    lb = Listbox(win, yscrollcommand=scrollbar.set, width=60)
    for f in files:
        lb.insert(END, f)
    lb.pack(side=tk.LEFT, fill=tk.BOTH)
    scrollbar.config(command=lb.yview)

    def on_select(event):
        idx = lb.curselection()
        if not idx:
            return
        filename = files[idx[0]]
        path = os.path.join(BEST_DIR, filename)
        with open(path, "r") as f:
            bits = f.read().strip()

        detail = tk.Toplevel(win)
        detail.title(filename)
        tk.Label(detail, text=f"Файл: {filename}\nДлина: {len(bits)} бит").pack(pady=5)
        tk.Message(detail, text=bits[:256] + ("..." if len(bits) > 256 else ""), width=500).pack(pady=5)

        def send_now():
            send_file(path)
        tk.Button(detail, text="📡 Отправить", command=send_now).pack(pady=5)

    lb.bind("<<ListboxSelect>>", on_select)


def send_file(path=FINAL_FILE):
    """Отправка кода"""
    if not os.path.exists(path):
        messagebox.showwarning("Ошибка", f"Нет файла {path}")
        return

    with open(path, "r") as f:
        bits = f.read().strip()
    if not bits:
        return

    data = bytearray(int(bits[i:i+8], 2) for i in range(0, len(bits), 8))

    ser = serial.Serial(TX_port or PORT, BAUD, timeout=1)
    for i in range(ATTEMPTS):
        ser.write(data)
        time.sleep(DELAY)
    ser.close()

    messagebox.showinfo("Успех", f"Отправлено {len(data)} байт")


def settings():
    """Изменить настройки"""
    global PORT, BAUD, ATTEMPTS, DELAY
    PORT = simpledialog.askstring("Настройки", f"PORT (сейчас {PORT}):") or PORT
    BAUD = simpledialog.askinteger("Настройки", f"BAUD (сейчас {BAUD}):") or BAUD
    ATTEMPTS = simpledialog.askinteger("Настройки", f"Повторов (сейчас {ATTEMPTS}):") or ATTEMPTS
    DELAY = simpledialog.askfloat("Настройки", f"Задержка (сейчас {DELAY} сек):") or DELAY
    messagebox.showinfo("Настройки", f"Обновлено:\nPORT={PORT}\nBAUD={BAUD}\nATTEMPTS={ATTEMPTS}\nDELAY={DELAY}")


# ===== GUI =====
root = tk.Tk()
root.title("RF Control 433 MHz")

frame = tk.Frame(root, padx=20, pady=20)
frame.pack()

tk.Label(frame, text="RF Control Panel", font=("Arial", 16)).pack(pady=10)

tk.Button(frame, text=" select port", width=35, command=select_port).pack(pady=5)
tk.Button(frame, text="RX port", command=select_rx_port).pack(pady=3)
tk.Button(frame, text="TX port", command=select_tx_port).pack(pady=3)
tk.Button(frame, text=" Захватить сигнал", width=35, command=capture_signal).pack(pady=5)
tk.Button(frame, text=" Декодировать сигнал", width=35, command=decode_signal).pack(pady=5)
tk.Button(frame, text=" Найти повторяющийся код", width=35, command=find_pattern).pack(pady=5)
tk.Button(frame, text=" Сохранить в лучшие", width=35, command=save_best).pack(pady=5)
tk.Button(frame, text=" Список сохранённых кодов", width=35, command=list_codes).pack(pady=5)
tk.Button(frame, text=" Отправить последний код", width=35, command=lambda: send_file(FINAL_FILE)).pack(pady=5)
tk.Button(frame, text=" Настройки", width=35, command=settings).pack(pady=5)
tk.Button(frame, text=" Выход", width=35, command=root.quit).pack(pady=5)

root.mainloop() 

