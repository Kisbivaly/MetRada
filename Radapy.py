import os
import sys
import time
import datetime
import requests
import ctypes

def get_latest_image_url():
    # Kérjünk le 10 perccel korábbi UTC időpontot
    now_utc = datetime.datetime.utcnow() - datetime.timedelta(minutes=10)
    # Kerekítés az utolsó 10 percre osztható időpontra
    rounded_time = now_utc - datetime.timedelta(minutes=now_utc.minute % 10, seconds=now_utc.second, microseconds=now_utc.microsecond)
    formatted_time = rounded_time.strftime('%Y%m%d_%H%M')
    image_url = f"https://www.met.hu/img/RccW/RccW{formatted_time}.jpg"
    return image_url

def download_image(url, save_path):
    response = requests.get(url)
    if response.status_code == 200:
        with open(save_path, 'wb') as file:
            file.write(response.content)
        return True
    return False

def set_background_image(image_path):
    # Windows háttérkép beállítása
    ctypes.windll.user32.SystemParametersInfoW(20, 0, image_path, 3)

def main():
    # Az aktuális futtatható fájl (exe vagy .py) mappájának lekérdezése
    if getattr(sys, 'frozen', False):
        # Ha exe-be van csomagolva
        app_path = os.path.dirname(sys.executable)
    else:
        # Ha sima python szkriptként fut
        app_path = os.path.dirname(os.path.abspath(__file__))
    
    # Létrehozzuk a "képek" nevű mappát az exe mappájában
    images_folder = os.path.join(app_path, "képek")
    os.makedirs(images_folder, exist_ok=True)

    # Az új kép neve, amit mindig felülírunk
    image_path = os.path.join(images_folder, "image.jpg")

    while True:
        # Kép letöltése és felülírása
        image_url = get_latest_image_url()
        
        if download_image(image_url, image_path):
            set_background_image(image_path)
            print(f"Háttérkép beállítva: {image_path}")
        else:
            print("Kép letöltése sikertelen.")

        # 10 perc várakozás
        time.sleep(600)

if __name__ == "__main__":
    main()
