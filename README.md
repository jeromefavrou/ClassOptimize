# ClassOptimize 🚀

Optimisez vos classes facilement avec **ClassOptimize**.  

---

## 📦 Téléchargement du binaire

Téléchargez la dernière version ici :  
[Releases GitHub](https://github.com/jeromefavrou/ClassOptimize/releases/tag/ClassOptimize)

---
## 🛠️ Installation sur Ubuntu via PPA

1. Ajouter depuis le dépôt PPA :  
   ```bash
   sudo mkdir -p /etc/apt/keyrings
   curl -fsSL https://github.com/jeromefavrou/ClassOptimize/raw/refs/heads/main/pubKey.gpg | sudo tee /etc/apt/keyrings/pubKeyClassOptimize.gpg > /dev/null
   sudo add-apt-repository ppa:jeromefavrou/classoptimize
   sudo apt update
   sudo apt install classoptimize
   

---
## 🛠️ Installation via Build & .deb local

1. compilation et pakaging local :  
   ```bash
   chmod +x BuildAndDebGenScript
   ./BuildAndDebGenScript
   sudo dpkg -i ../classoptimize_1.0-0_amd64.deb
   
