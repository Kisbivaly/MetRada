#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <windows.h>
#include <curl/curl.h>
#include <direct.h> // mkdir

// Segédfüggvény a letöltéshez
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::ofstream* file = static_cast<std::ofstream*>(userp);
    file->write(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

// Kép letöltése a megadott URL-ről és mentése a fájlrendszerbe
bool download_image(const std::string& url, const std::string& save_path) {
    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    
    if(curl) {
        std::ofstream file(save_path, std::ios::binary);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return (res == CURLE_OK);
    }
    return false;
}

// Háttérkép beállítása Windows rendszeren
void set_background_image(const std::string& image_path) {
    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 0, (void*)image_path.c_str(), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
}

// Kép URL generálása az aktuális UTC idő alapján, kerekítve a legutóbbi 10 percre
std::string get_latest_image_url() {
    auto now = std::chrono::system_clock::now();
    now -= std::chrono::minutes(10); // 10 perccel korábbi idő
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    
    std::tm utc_time;
    gmtime_s(&utc_time, &t);  // UTC idő átalakítása

    // Kerekítés a legutóbbi 10 percre
    utc_time.tm_min -= utc_time.tm_min % 10;
    utc_time.tm_sec = 0;
    
    // Formázott idő generálása az URL-hez
    std::ostringstream oss;
    oss << std::put_time(&utc_time, "%Y%m%d_%H%M");
    
    std::string formatted_time = oss.str();
    std::string image_url = "https://www.met.hu/img/RccW/RccW" + formatted_time + ".jpg";
    
    return image_url;
}

int main() {
    // Képek mappa létrehozása, ha nem létezik
    const char* images_folder = "képek";
    _mkdir(images_folder);
    
    std::string image_path = std::string(images_folder) + "/image.jpg";

    while (true) {
        // Kép letöltése
        std::string image_url = get_latest_image_url();
        std::cout << "Letöltés URL: " << image_url << std::endl;
        
        if (download_image(image_url, image_path)) {
            set_background_image(image_path);
            std::cout << "Háttérkép beállítva: " << image_path << std::endl;
        } else {
            std::cout << "Kép letöltése sikertelen." << std::endl;
        }
        
        // 10 perc várakozás
        std::this_thread::sleep_for(std::chrono::minutes(10));
    }

    return 0;
}
