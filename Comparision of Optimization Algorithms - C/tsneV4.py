import pandas as pd
import numpy as np
from sklearn.manifold import TSNE
import matplotlib.pyplot as plt

# CSV dosyalarını okuma
#file_names = ['adam_weights_a.csv', 'adam_weights_b.csv', 'adam_weights_c.csv', 'adam_weights_d.csv', 'adam_weights_e.csv']
file_names = ['sgd_weights_a.csv', 'sgd_weights_b.csv', 'sgd_weights_c.csv', 'sgd_weights_d.csv', 'sgd_weights_e.csv']
#file_names = ['gd_weights_a.csv', 'gd_weights_b.csv', 'gd_weights_c.csv', 'gd_weights_d.csv', 'gd_weights_e.csv']

dataframes = []

for file_name in file_names:
    df = pd.read_csv(file_name)
    # Son 1 sütunu düşürme
    df = df.iloc[:, :-1]
    dataframes.append(df)

# DataFrame birleştirme
data = pd.concat(dataframes, ignore_index=True)

# Verilerde eksik değer kontrolü
print(data.isnull().sum())

# İlk 5 satırı kontrol etme
print(data.head(5))

# Epoch numarasını ayırma
epochs = data['epoch']
print(epochs.head(5))

# Epoch sütununu çıkararak sadece weights sütunlarını alma
weights = data.iloc[:, 1:]  
print(weights.head(5))

# t-SNE dönüşümü
tsne = TSNE(n_components=2, perplexity=150, random_state=42)
weights_2d = tsne.fit_transform(weights)

# görselleştirme
plt.figure(figsize=(10, 8))
scatter = plt.scatter(weights_2d[:, 0], weights_2d[:, 1], c=epochs, cmap='viridis', alpha=0.7)
plt.colorbar(scatter, label='Epoch Number')
plt.title('SGD Weights t-SNE Visualization')
plt.xlabel('t-SNE Dimension 1')
plt.ylabel('t-SNE Dimension 2')
plt.savefig("SGD_TSNE.png")
plt.show()


