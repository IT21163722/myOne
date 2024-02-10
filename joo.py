import cv2
import tkinter as tk
from tkinter import filedialog, messagebox

class VideoPlayerApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Video Player")

        self.video_path = None
        self.cap = None

        self.canvas = tk.Canvas(root, width=640, height=360)
        self.canvas.pack()

        menu_bar = tk.Menu(root)
        root.config(menu=menu_bar)

        file_menu = tk.Menu(menu_bar, tearoff=0)
        menu_bar.add_cascade(label="File", menu=file_menu)
        file_menu.add_command(label="Open Video", command=self.open_video)
        file_menu.add_separator()
        file_menu.add_command(label="Exit", command=root.destroy)

        play_button = tk.Button(root, text="Play", command=self.play_video)
        play_button.pack(pady=10)

    def open_video(self):
        file_path = filedialog.askopenfilename(title="Select a video file", filetypes=[("Video files", "*.mp4;*.avi;*.mkv")])

        if file_path:
            self.video_path = file_path
            self.cap = cv2.VideoCapture(self.video_path)

            # Get video dimensions
            width = int(self.cap.get(3))
            height = int(self.cap.get(4))

            # Resize the Tkinter canvas to match video dimensions
            self.canvas.config(width=width, height=height)

            messagebox.showinfo("Video Player", f"Opened: {self.video_path}")

    def play_video(self):
        if self.cap is None:
            messagebox.showwarning("Video Player", "Please open a video first.")
            return

        while True:
            ret, frame = self.cap.read()
            if not ret:
                break

            # Convert BGR to RGB
            frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

            # Convert RGB to PhotoImage
            photo = tk.PhotoImage(width=frame_rgb.shape[1], height=frame
