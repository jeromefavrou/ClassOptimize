# ClassOptimize 🚀

✏️  Outils pour la classe 
🎲 Gestion de groupes / ateliers


créer groupes équilibrés.

contraintes (niveau, comportement, affinités)

génération rapide de groupes.

👉 Pas IA : Simple Algorithme Génétique.

---

## 📦 Téléchargement du binaire

Téléchargez la dernière version ici :  

[Releases GitHub V1.0 ( Windows ) ](https://github.com/jeromefavrou/ClassOptimize/releases/tag/ClassOptimize)
[Releases GitHub V1.1 ( Linux seulement ) ](https://github.com/jeromefavrou/ClassOptimize/releases/tag/ClassOptimize_1.1-0.jammy_amd64)

---
## 🛠️ Installation sur Ubuntu via PPA

1. Ajouter depuis le dépôt PPA :  
   ```bash
   sudo mkdir -p /etc/apt/keyrings
   curl -fsSL https://github.com/jeromefavrou/ClassOptimize/raw/refs/heads/main/pubKey.gpg | sudo tee /etc/apt/keyrings/pubKeyClassOptimize.gpg > /dev/null
   sudo add-apt-repository ppa:jeromefavrou/classoptimize
   sudo apt update
   sudo apt install classoptimize
   ClassOptimize
   

---
## 🛠️ Installation via Build & .deb local

1. compilation et pakaging local :  
   ```bash
   chmod +x BuildAndDebGenScript
   ./BuildAndDebGenScript
   sudo dpkg -i ../classoptimize_1.0-0_amd64.deb
   ClassOptimize
   
