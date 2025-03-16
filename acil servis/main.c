#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struct tanýmlarý
typedef struct {
    char tc[12];
    char isim[50];
    int hastaNo;
} Hasta;

typedef struct {
    char hastaSoz[256];
    char doktorGorus[256];
} Sikayet;

typedef struct {
    char recete[5][50];
    int receteSayisi;
} Recete;

// Ýlaç listesi
char* ilaclar[] = {
    "Parol",
    "Augmentin",
    "Klavunat",
    "Ventolin",
    "Aferin Forte"
};
int ilacSayisi = 5;

// Fonksiyon prototipleri
void adminMenu();
void doktorMenu();
void hastaKayit();
void hastaMenu();
void hastaListele();
void hastaAra();
void teshisEkrani(Hasta hasta);
void sikayetEkrani();
void receteEkrani();
int tcDogrula(char *tc);

int hastaSayac = 1;
Hasta hastalar[100];

int main() {
    char kullaniciAdi[20], sifre[20];
    while(1) {
        printf("=== HASTANE ACIL POLIKLINIK SISTEMI ===\n");
        printf("Kullanici Adi: ");
        scanf("%s", kullaniciAdi);
        printf("Sifre: ");
        scanf("%s", sifre);

        if(strcmp(kullaniciAdi, "admin") == 0 && strcmp(sifre, "admin") == 0) {
            adminMenu();
        } else if(strcmp(kullaniciAdi, "doktor") == 0 && strcmp(sifre, "doktor") == 0) {
            doktorMenu();
        } else {
            printf("Hatali giris! Tekrar deneyin.\n");
        }
    }
    return 0;
}

// Admin menüsü
void adminMenu() {
    int secim;
    do {
        printf("\n--- Admin Menusu ---\n");
        printf("1. Doktor Kayit (Sadece simule ediyor)\n");
        printf("2. Hasta Kayit\n");
        printf("3. Hasta Menusu\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        switch(secim) {
            case 1:
                printf("Doktor kayit sistemi burada (simulasyon).\n");
                break;
            case 2:
                hastaKayit();
                break;
            case 3:
                hastaMenu();
                break;
            case 0:
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    } while(secim != 0);
}

// Doktor menüsü
void doktorMenu() {
    int secim;
    do {
        printf("\n--- Doktor Menusu ---\n");
        printf("1. Hasta Kayit\n");
        printf("2. Hasta Menusu\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        switch(secim) {
            case 1:
                hastaKayit();
                break;
            case 2:
                hastaMenu();
                break;
            case 0:
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    } while(secim != 0);
}

// Hasta menüsü
void hastaMenu() {
    int secim;
    do {
        printf("\n--- Hasta Menusu ---\n");
        printf("1. Tum Hastalari Listele\n");
        printf("2. TC ile Hasta Ara\n");
        printf("0. Geri Don\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        switch(secim) {
            case 1:
                hastaListele();
                break;
            case 2:
                hastaAra();
                break;
            case 0:
                printf("Ana menuye donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    } while(secim != 0);
}

// Hasta listeleme fonksiyonu
void hastaListele() {
    printf("\n--- KAYITLI HASTALAR ---\n");
    for(int i = 0; i < hastaSayac - 1; i++) {
        printf("Hasta No: %d | TC: %s | Isim: %s\n", hastalar[i].hastaNo, hastalar[i].tc, hastalar[i].isim);
    }
    if(hastaSayac == 1) {
        printf("Henuz kayitli hasta yok.\n");
    }
}

// TC ile hasta arama
void hastaAra() {
    char tc[12];
    printf("Aranacak hasta TC: ");
    scanf("%s", tc);

    int bulundu = 0;
    for(int i = 0; i < hastaSayac - 1; i++) {
        if(strcmp(hastalar[i].tc, tc) == 0) {
            printf("Hasta Bulundu! Hasta No: %d | TC: %s | Isim: %s\n", hastalar[i].hastaNo, hastalar[i].tc, hastalar[i].isim);
            bulundu = 1;
            break;
        }
    }
    if(!bulundu) {
        printf("Hasta bulunamadi!\n");
    }
}

// Hasta kayýt (TC doðrulama ile birlikte)
void hastaKayit() {
    Hasta yeniHasta;

    // TC doðrulama
    do {
        printf("Hasta TC (11 haneli): ");
        scanf("%s", yeniHasta.tc);
        if(!tcDogrula(yeniHasta.tc)) {
            printf("Hata: TC 11 haneli ve sadece rakamlardan olusmalidir!\n");
        }
    } while(!tcDogrula(yeniHasta.tc));

    printf("Hasta Isim: ");
    scanf("%s", yeniHasta.isim);
    yeniHasta.hastaNo = hastaSayac++;
    hastalar[yeniHasta.hastaNo - 1] = yeniHasta;
    printf("Hasta kayit edildi! Hasta No: %d\n", yeniHasta.hastaNo);
    teshisEkrani(yeniHasta);
}

// TC doðrulama fonksiyonu
int tcDogrula(char *tc) {
    if(strlen(tc) != 11) {
        return 0;
    }
    for(int i = 0; i < 11; i++) {
        if(!isdigit(tc[i])) {
            return 0;
        }
    }
    return 1;
}

// Teshis ekrani
void teshisEkrani(Hasta hasta) {
    int secim;
    do {
        printf("\n--- Teshis Ekrani ---\n");
        printf("Hasta: %s (No: %d)\n", hasta.isim, hasta.hastaNo);
        printf("1. Hasta Sikayet\n");
        printf("2. Recete Yaz\n");
        printf("0. Ana Menuye Don\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        switch(secim) {
            case 1:
                sikayetEkrani();
                break;
            case 2:
                receteEkrani();
                break;
            case 0:
                printf("Ana menuye donuluyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    } while(secim != 0);
}

// Sikayet ekrani
void sikayetEkrani() {
    Sikayet skyt;
    printf("Hasta Sozleri: ");
    getchar(); // Buffer temizle
    fgets(skyt.hastaSoz, 256, stdin);
    printf("Doktor Gorusu: ");
    fgets(skyt.doktorGorus, 256, stdin);
    printf("Sikayet kaydedildi.\n");
}

// Recete ekrani
void receteEkrani() {
    Recete recete;
    recete.receteSayisi = 0;
    int secim;
    do {
        printf("\n--- Recete Ekrani ---\n");
        printf("1. Tum ilaclari Listele\n");
        printf("2. Receteye ilac Ekle\n");
        printf("3. Receteyi Goster\n");
        printf("0. Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);
        switch(secim) {
            case 1:
                for(int i = 0; i < ilacSayisi; i++) {
                    printf("%d. %s\n", i+1, ilaclar[i]);
                }
                break;
            case 2: {
                int ilacSecim;
                printf("ilac numarasini secin: ");
                scanf("%d", &ilacSecim);
                if(ilacSecim > 0 && ilacSecim <= ilacSayisi && recete.receteSayisi < 5) {
                    strcpy(recete.recete[recete.receteSayisi], ilaclar[ilacSecim - 1]);
                    recete.receteSayisi++;
                    printf("ilac eklendi.\n");
                } else {
                    printf("Gecersiz secim veya recete dolu.\n");
                }
                break;
            }
            case 3:
                printf("Hastaya verilen ilaclar:\n");
                for(int i = 0; i < recete.receteSayisi; i++) {
                    printf("- %s\n", recete.recete[i]);
                }
                break;
            case 0:
                printf("Recete ekranindan cikiliyor...\n");
                break;
            default:
                printf("Gecersiz secim!\n");
        }
    } while(secim != 0);
}

