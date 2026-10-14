# Upload to GitHub — beginner guide

1. Download and extract the ZIP archive. Keep the top-level folder `voltage-stabilizer-arduino` intact.
2. Sign in at https://github.com and select **+ → New repository**.
3. Repository name: `arduino-automatic-voltage-stabilizer` (or `voltage-stabilizer-arduino`).
4. Description: `Arduino-based relay voltage stabilizer | Proteus schematic documentation and reconstructed control firmware`.
5. Select **Public** for a portfolio repository, and **do not initialize** with a GitHub README, `.gitignore`, or license (the ZIP already includes its own README and `.gitignore`).
6. Click **Create repository**.
7. For browser upload, choose **uploading an existing file**, drag the *contents* of the extracted project folder (including `.github` if your file browser exposes hidden files), and click **Commit changes**. GitHub's web uploader may not preserve dotfiles from some file managers; if it doesn't, use Git commands below.

## Git commands (recommended)

Open Terminal inside the extracted `voltage-stabilizer-arduino` folder, then run:

```bash
git init
git add .
git commit -m "Document Arduino voltage stabilizer and reconstructed firmware"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/arduino-automatic-voltage-stabilizer.git
git push -u origin main
```

Replace `YOUR_USERNAME` with your GitHub username. Authenticate using the GitHub flow shown in your terminal (a regular account password is not accepted for Git-over-HTTPS). If Git asks for your name/email, configure `git config --global user.name "Your Name"` and `git config --global user.email "you@example.com"`.

## Portfolio presentation

Keep the original screenshot, use the README overview, and show the reconstructed code transparently. If you later find the **original** `.ino` or native Proteus files, add them in a labeled directory and update the provenance section. Do not claim the mathematical example output is measured.
