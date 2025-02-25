import pandas as pd
import matplotlib.pyplot as plt

# CSV dosyalarını okuma
gd_data = pd.read_csv("gd_logs_d.csv")
sgd_data = pd.read_csv("sgd_logs_d.csv")
adam_data = pd.read_csv("adam_logs_d.csv")
"""
gd_data = gd_data[:50]
sgd_data = sgd_data[:50]
adam_data = adam_data[:50]"""

# Epoch sayısını bulma
epochs = range(1, len(gd_data)+ 1)

# Zamanı sıfırdan başlatma
gd_data["Time_Elapsed"] -= gd_data["Time_Elapsed"].iloc[0]
sgd_data["Time_Elapsed"] -= sgd_data["Time_Elapsed"].iloc[0]
adam_data["Time_Elapsed"] -= adam_data["Time_Elapsed"].iloc[0]

# Grafik oluşturma
plt.figure(figsize=(12, 6))

# Train Accuracy grafikleri
plt.plot(epochs, gd_data["Train_Accuracy"], label="GD Train Accuracy", linestyle="--", color="blue")
plt.plot(epochs, sgd_data["Train_Accuracy"], label="SGD Train Accuracy", linestyle="--", color="orange")
plt.plot(epochs, adam_data["Train_Accuracy"], label="Adam Train Accuracy", linestyle="--", color="green")

# Test Accuracy grafikleri
plt.plot(epochs, gd_data["Test_Accuracy"], label="GD Test Accuracyss", color="blue")
plt.plot(epochs, sgd_data["Test_Accuracy"], label="SGD Test Accuracy", color="orange")
plt.plot(epochs, adam_data["Test_Accuracy"], label="Adam Test Accuracy", color="green")

# Grafik ayarları
plt.title("w4 : Accuracy Comparison Over Epoch: GD vs SGD vs Adam")
plt.xlabel("Epochs")
plt.ylabel("Accuracy(%)")
plt.legend()
plt.grid(True)

# Grafiği kaydetme ve gösterme
plt.savefig("w4_Accuracy_Epoch.png")
plt.show()


# Train Accuracy zamana göre
plt.plot(gd_data["Time_Elapsed"], gd_data["Train_Accuracy"], label="GD Train Accuracy", linestyle="--", color="blue")
plt.plot(sgd_data["Time_Elapsed"], sgd_data["Train_Accuracy"], label="SGD Train Accuracy", linestyle="--", color="orange")
plt.plot(adam_data["Time_Elapsed"], adam_data["Train_Accuracy"], label="Adam Train Accuracy", linestyle="--", color="green")

# Test Accuracy zamana göre
plt.plot(gd_data["Time_Elapsed"], gd_data["Test_Accuracy"], label="GD Test Accuracy", color="blue")
plt.plot(sgd_data["Time_Elapsed"], sgd_data["Test_Accuracy"], label="SGD Test Accuracy", color="orange")
plt.plot(adam_data["Time_Elapsed"], adam_data["Test_Accuracy"], label="Adam Test Accuracy", color="green")

# Grafik ayarları
plt.title("w4 : Accuracy Comparison Over Time: GD vs SGD vs Adam")
plt.xlabel("Time (seconds)")
plt.ylabel("Accuracy (%)")
plt.legend()
plt.grid(True)

# Grafiği kaydetme ve gösterme
plt.savefig("w4_Accuracy_time_.png")
plt.show()


# Grafik oluşturma
plt.figure(figsize=(12, 6))

# Train Loss grafikleri
plt.plot(epochs, gd_data["Train_Loss"], label="GD Train Loss", linestyle="--", color="blue")
plt.plot(epochs, sgd_data["Train_Loss"], label="SGD Train Loss", linestyle="--", color="orange")
plt.plot(epochs, adam_data["Train_Loss"], label="Adam Train Loss", linestyle="--", color="green")

# Test Loss grafikleri
plt.plot(epochs, gd_data["Test_Loss"], label="GD Test Loss", color="blue")
plt.plot(epochs, sgd_data["Test_Loss"], label="SGD Test Loss", color="orange")
plt.plot(epochs, adam_data["Test_Loss"], label="Adam Test Loss", color="green")

# Grafik ayarları
plt.title("w4 : Loss Comparison Over Epoch: GD vs SGD vs Adam")
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.legend()
plt.grid(True)

# Grafiği kaydetme ve gösterme
plt.savefig("w4_loss_epoch.png")
plt.show()

# Grafik oluşturma
plt.figure(figsize=(12, 6))

# Train Loss zamana göre
plt.plot(gd_data["Time_Elapsed"], gd_data["Train_Loss"], label="GD Train Loss", linestyle="--", color="blue")
plt.plot(sgd_data["Time_Elapsed"], sgd_data["Train_Loss"], label="SGD Train Loss", linestyle="--", color="orange")
plt.plot(adam_data["Time_Elapsed"], adam_data["Train_Loss"], label="Adam Train Loss", linestyle="--", color="green")

# Test Loss zamana göre
plt.plot(gd_data["Time_Elapsed"], gd_data["Test_Loss"], label="GD Test Loss", color="blue")
plt.plot(sgd_data["Time_Elapsed"], sgd_data["Test_Loss"], label="SGD Test Loss", color="orange")
plt.plot(adam_data["Time_Elapsed"], adam_data["Test_Loss"], label="Adam Test Loss", color="green")

# Grafik ayarları
plt.title("w4 : Loss Comparison Over Time: GD vs SGD vs Adam")
plt.xlabel("Time (seconds)")
plt.ylabel("Loss")
plt.legend()
plt.grid(True)

# Grafiği kaydetme ve gösterme
plt.savefig("w4_loss_time.png")
plt.show()
