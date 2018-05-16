
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Kayit{
    char deger;
    int enter_alt_satira_gecis;
    struct Kayit *sonraki, *onceki;
};
struct Kayit *ilk, *son, *imlec, *gecici1,*gecici2, *gecici3;

struct Shift{
    char deger;
    struct Kayit *sonraki, *onceki;
};
struct Shift *shift_ilk, *shift_son, *shift_imlec, *shift_gecici1;

int imlec_konum, cumle_uzunluk, enter_sayisi, shift_konum=0,shift_eleman_sayisi=0, ctrlA_tiklama=0, sonraki_sayfa=0, kontrol_sayfa=0,sayfa_no=1;
int secim_karakter=0;

char *shift_cumle;
char shift_dizi_cumle[400];

int menu_secim_kontrol=0,secilen_elenan_sayisi=0;

FILE *fp,*dosya1,*dosya2,*dosya3;
char dosya_adi[50];

void Baslangic_Ayar();
void Ekle(char karakter);
void Sil_Space();
void Sil_Delete();
void Alt_Satira_Gec();
void Imlec_Koy();
void Listele();
void Yukari_Ok();
void Asagi_Ok();
void Sag_Ok();
void Sol_Ok();
void Shift_Eleman_Ekle();
void Shift_Ayarlar();
void Ctrl_A();
void Ctrl_Kopyala();
void Ctrl_Kes();
void Ctrl_Yapistir();
void Eleman_Secim_Sira();

void Anasayfa();
void Bilgilendirme();
void Kaydet();
void Kayit_Ac();
void Kayit_Ac_2();
void Kayit_Sil();

int main(){
    Baslangic_Ayar();
    system("COLOR F0");
    if(menu_secim_kontrol==0){
        Anasayfa();
    }
    Bilgilendirme();
    int giris;
    char girilen_karakter;
    Listele();
    while((giris=_getch())!=27){
        girilen_karakter=giris;
        if(girilen_karakter==-32){
            giris=_getch();
            girilen_karakter=giris;
            if(girilen_karakter==75){
                Sol_Ok();
                shift_konum=imlec_konum;
                ctrlA_tiklama=0;

                if(imlec_konum%100==99){
                    sayfa_no--;
                    imlec->enter_alt_satira_gecis=0;
                }
            }
            else if(girilen_karakter==77){
                Sag_Ok();
                shift_konum=imlec_konum;
                ctrlA_tiklama=0;
            }
            else if(girilen_karakter==72){
                Yukari_Ok();
                shift_konum=imlec_konum;
                ctrlA_tiklama=0;
            }
            else if(girilen_karakter==80){
                Asagi_Ok();
                shift_konum=imlec_konum;
                ctrlA_tiklama=0;
            }
            else if(giris==83){
                Sil_Delete();
                shift_konum=imlec_konum;
                ctrlA_tiklama=0;
            }
        }
        else if(girilen_karakter==0){
            giris=_getch();
            girilen_karakter=giris;
            if(girilen_karakter==59){
                ///F1 TUSU
                ilk=NULL;
                son=NULL;
                Baslangic_Ayar();
                Anasayfa();
            }
        }
        else if(girilen_karakter==224){
            giris=_getch();
            girilen_karakter=giris;
            if(girilen_karakter==115){
                printf("sol");
                getch();
            }
            else if(girilen_karakter==116){
                printf("sag");
                getch();
            }
            else if(girilen_karakter==141){
                printf("yukari");
                getch();
            }
            else if(girilen_karakter==145){
                printf("asagi");
                getch();
            }
        }
        else if(giris==49){
            //1
            if(shift_konum>0)
                shift_konum--;
        }
        else if(giris==51){
            //3
            if(shift_konum<cumle_uzunluk){
                shift_konum++;
            }
        }
        else if(giris==50){
            //2
            if(imlec_konum+10<cumle_uzunluk){
                shift_konum+=10;
            }
        }
        else if(giris==53){
            //5
            if(imlec_konum-10>0){
                shift_konum=shift_konum-10;
                secilen_elenan_sayisi+=10;
            }
        }
        else if(giris==1){
            ///tumunu sec
            Ctrl_A();
        }
        else if(giris==3){
            ///kopyala
            Ctrl_Kopyala();
        }
        else if(giris==22){
            ///yapistir
            Ctrl_Yapistir();
            shift_konum=imlec_konum;
            ctrlA_tiklama=0;
        }
        else if(giris==24){
            ///KES;
            if(shift_konum!=imlec_konum)
            {
                Ctrl_Kes();
                shift_konum=imlec_konum;
                ctrlA_tiklama=0;
            }
            else if(ctrlA_tiklama){
                Ctrl_Kes();
            }
        }
        else if(giris==19){
            Kayit();
        }
        else if(giris==15){
            Kayit_Ac();
        }
        else if(giris==13){
            Alt_Satira_Gec();
        }
        else if(giris==8){
            Sil_Space();
        }
        else{
            fputc(girilen_karakter,dosya1);
            Ekle(girilen_karakter);
        }
        //system("cls");
        Listele();
    }
    exit(0);
    return 0;
}

void Baslangic_Ayar(){
    imlec_konum=0;
    cumle_uzunluk=0;
    enter_sayisi=0;
    dosya1=fopen("temp.txt","w");
    gecici2=malloc(sizeof(struct Kayit));
    gecici3=malloc(sizeof(struct Kayit));
    imlec=malloc(sizeof(struct Kayit));
    imlec->deger='|';
    imlec->enter_alt_satira_gecis=0;
    imlec->sonraki=NULL;
    imlec->onceki=NULL;
    ilk=imlec;
    son=imlec;
    ilk=son;

    shift_konum=imlec_konum;
    shift_ilk=malloc(sizeof(struct Shift));
    shift_son=malloc(sizeof(struct Shift));
    shift_gecici1=malloc(sizeof(struct Shift));
    shift_imlec=malloc(sizeof(struct Shift));
    shift_ilk=imlec;
    shift_son=shift_ilk;
    shift_imlec=shift_son;
    shift_gecici1=shift_imlec;
}
void Ekle(char karakter){
    if(imlec_konum==0){///eger imlec bastaysa
        gecici1=malloc(sizeof(struct Kayit));
        gecici1->deger=karakter;
        gecici1->enter_alt_satira_gecis=0;
        gecici1->onceki=NULL;
        gecici1->sonraki=imlec;
        imlec->onceki=gecici1;
        ilk=gecici1;
    }
    else if(imlec_konum==(cumle_uzunluk)){///eger imlec sondaysa
        gecici1=malloc(sizeof(struct Kayit));
        gecici1->deger = karakter;
        gecici1->enter_alt_satira_gecis=0;
        gecici1->onceki=imlec->onceki;
        gecici1->sonraki=imlec;

        imlec->onceki->sonraki=gecici1;
        imlec->onceki=gecici1;
        imlec->sonraki=NULL;
        son=imlec;
    }
    else{///eger imlec ortalardaysa
        gecici1=malloc(sizeof(struct Kayit));
        gecici1->deger=karakter;
        gecici1->enter_alt_satira_gecis=sayfa_no;
        gecici1->onceki=imlec->onceki;
        gecici1->sonraki=imlec;

        imlec->onceki->sonraki=gecici1;
        imlec->onceki=gecici1;
    }
    cumle_uzunluk++;
    imlec_konum++;
    shift_konum=imlec_konum;
    ctrlA_tiklama=0;
    sonraki_sayfa++;

}

void Shift_Ekle(){
    int sayac1=0,sayac2=0,sayac3=0;
    if(shift_konum>imlec_konum){
        sayac1=shift_konum; ///eleman sayisi
        sayac2=sayac1-imlec_konum;
        char dizi[sayac1+1];
        gecici1=imlec;
        while(sayac1!=imlec_konum){
            gecici1=gecici1->onceki;
            sayac1--;
            sayac3++;
        }
        while(sayac2!=0){
            gecici1=gecici1->sonraki;
            dizi[sayac3]=gecici1->deger;
            sayac2--;
        }
        Ctrl_Yapistir(dizi,sayac3+1);
    }
}

void Imlec_Koy(){
    if(imlec_konum==0){///ilk eleman imlec olacak
        if(cumle_uzunluk==0){///karakterin basta olmasi ve yaninda bir eleman olmamasi durumu
            imlec->sonraki=NULL;
            imlec->onceki=NULL;
            ilk=imlec;
            son=ilk;
        }
        else if(cumle_uzunluk>0){///karakterin basta, yaninda en az bir eleman var.
            gecici1=ilk;
            imlec->sonraki=gecici1;
            imlec->onceki=NULL;
            ilk->onceki=imlec;
            ilk=imlec;
        }
    }
    else if(imlec_konum==cumle_uzunluk){///karakterin sonda olma durumu
        gecici1=son;
        imlec->onceki=gecici1;
        imlec->sonraki=NULL;
        son->sonraki=imlec;
        son=imlec;
    }
    else{///karakterin basta ve sonda olmama durumu
        gecici1=ilk;
        int sayac=0;
        while(sayac!=(imlec_konum-1)){
            gecici1=gecici1->sonraki; ///imlec
            sayac++;
        }
        gecici2=gecici1;
        gecici3=gecici1->sonraki;

        imlec->onceki=gecici2;
        imlec->sonraki=gecici3;
        gecici2->sonraki=imlec;
        gecici3->onceki=imlec;
    }
}
void Imlec_Cikar(){
    if(imlec_konum==0){///imlecin basta olma durumu
        if(cumle_uzunluk==1){///imlecin basta olmasi ve yaninda bir eleman olmamasi durumu
            gecici1=imlec->sonraki;
            gecici1->onceki=NULL;
            gecici1->sonraki=NULL;
            ilk=gecici1;
            son=ilk;
        }
        else if(cumle_uzunluk>1){///imlecin basta olmasi ve yaninda bir eleman olmamasi durumu
            gecici1=imlec->sonraki;
            gecici1->onceki=NULL;
            gecici1->sonraki=imlec->sonraki->sonraki;
            ilk=gecici1;
            imlec->onceki=NULL;
            imlec->sonraki=NULL;
        }
    }
    else if(imlec_konum==cumle_uzunluk){///imlecin sonda olma durumu
        gecici1=son->onceki;
        gecici1->sonraki=NULL;
        imlec->onceki=NULL;
        imlec->sonraki=NULL;
        son=gecici1;
    }
    else{///imlecin bas ve sonda olmama durumu
        gecici1=ilk;
        while(gecici1!=imlec){
            gecici1=gecici1->sonraki;///imlec
        }
        gecici2=imlec->onceki;
        gecici3=imlec->sonraki;
        gecici2->sonraki=gecici3;
        gecici3->onceki=gecici2;
        gecici1->sonraki=NULL;
        gecici1->onceki=NULL;
    }

}
void Listele(){
    gecici1=ilk;
    int kontrol1=imlec_konum;
    int kontrol2=1;
    if(secim_karakter<0) secim_karakter*=(-1);
    while((kontrol1/20)!=0){
        kontrol2+=20;
        kontrol1-=20;
    }
    while(kontrol2!=1){
        gecici1=gecici1->sonraki;
        kontrol2--;
    }
    system("CLS");
    int satir_bosluk=0,i=0;
    int renk_sayac=shift_konum;
    while(gecici1!=NULL && i!=20){
        satir_bosluk++;
        if(satir_bosluk%10==1 && satir_bosluk!=1){
            printf("\n");
            satir_bosluk=1;
        }
        i++;

        printf("%c",gecici1->deger);
        gecici1=gecici1->sonraki;
    }
    i=0;

    printf("\n\n\n\n***************************************************");
    printf("\nSayfa No : %d",(imlec_konum/20)+1);
    printf("\nImlec Satir No : %d",(cumle_uzunluk/10)+1);
    printf("\nCumle Uzunlugu : %d",cumle_uzunluk+1);
    printf("\nImlecin Bulundugu Konum : %d",imlec_konum+1);
    if(shift_dizi_cumle[i]!=NULL){
        int j;
        printf("\nSecilen Elemanlar : ");
        for(j=0; j<secim_karakter; j++){
            printf("%c",shift_dizi_cumle[j]);
        }
    }
    printf("\n***************************************************");
}

void Yukari_Ok(){
    if(imlec_konum>=10){
        Imlec_Cikar();
        imlec_konum-=10;
        shift_konum=imlec_konum;
        Imlec_Koy();
    }
    else{
        ///birsey yapmasin
    }
}
void Asagi_Ok(){
    if(cumle_uzunluk-imlec_konum>=10){
        Imlec_Cikar();
        imlec_konum+=10;
        shift_konum=imlec_konum;
        Imlec_Koy();
    }
    else if(cumle_uzunluk-imlec_konum<10 && imlec_konum!=0){
        Imlec_Cikar();
        gecici1=son;
        gecici1->sonraki=imlec;
        imlec->onceki=gecici1;
        son=imlec;
        imlec_konum=cumle_uzunluk;
        shift_konum=imlec_konum;
    }
    else{
        ///bisey yapmasin.
    }
}
void Sag_Ok(){
    if(imlec_konum!=cumle_uzunluk){
        Imlec_Cikar();
        imlec_konum++;
        shift_konum=imlec_konum;
        Imlec_Koy();
    }
}
void Sol_Ok(){
    if(imlec_konum!=0){
        Imlec_Cikar();
        imlec_konum--;
        shift_konum=imlec_konum;
        Imlec_Koy();
    }
}
void Sil_Space(){
    if(imlec_konum==0){
        ///herhangi birsey yapma
    }
    else if(imlec_konum==cumle_uzunluk){///imlecin sonda olma durumu
        if(imlec_konum==1){
            gecici1=ilk;
            gecici1->sonraki=NULL;
            imlec->onceki=NULL;
            imlec->sonraki=NULL;
            son=imlec;
            ilk=son;
            cumle_uzunluk--;
            imlec_konum--;
            shift_konum=imlec_konum;
            sonraki_sayfa--;
        }
        else{
            gecici1=son->onceki->onceki;
            gecici1->sonraki=imlec;
            imlec->onceki=gecici1;
            imlec->sonraki=NULL;
            son=imlec;
            cumle_uzunluk--;
            imlec_konum--;
            shift_konum=imlec_konum;
            sonraki_sayfa--;
        }
    }
    else{///imlecin bas ve sonda olmama durumu
        if(imlec_konum==1){
            gecici1=ilk;
            imlec->sonraki=ilk->sonraki->sonraki;
            imlec->onceki=NULL;
            gecici1->sonraki=NULL;
            ilk=imlec;
            cumle_uzunluk--;
            imlec_konum--;
            shift_konum=imlec_konum;
            sonraki_sayfa--;
        }
        else{
            //printf("asd");
            //getch();
            gecici1=ilk;
            while(gecici1!=imlec){
                gecici1=gecici1->sonraki;///imlec
            }
            gecici1=gecici1->onceki;
            gecici2=gecici1->onceki;
            gecici3=gecici1->sonraki->sonraki;
            gecici2->sonraki=imlec;
            gecici3->onceki=imlec;
            imlec->sonraki=gecici3;
            imlec->onceki=gecici2;
            gecici1->sonraki=NULL;
            gecici1->onceki=NULL;
            cumle_uzunluk--;
            imlec_konum--;
            shift_konum=imlec_konum;
            sonraki_sayfa--;
        }
    }
}
void Sil_Delete(){
    if(imlec_konum==0){///imlecin basta olmasi durumu
        gecici1=ilk;
        if(gecici1->sonraki==NULL){

        }
        else if(gecici1->sonraki==son){
            son->onceki=NULL;
            imlec->sonraki=NULL;
            son=imlec;
            cumle_uzunluk--;
            sonraki_sayfa--;
        }
        else{
            gecici2=gecici1->sonraki;
            gecici3=gecici2->sonraki;
            gecici2->sonraki=NULL;
            gecici2->onceki=NULL;
            imlec->sonraki=gecici3;
            gecici3->onceki=imlec;
            cumle_uzunluk--;
            sonraki_sayfa--;
        }
    }
    else if(imlec_konum==cumle_uzunluk){///imlecin sonda olma durumu
        ///herhangi bir sey yapma
    }
    else{///imlecin bas ve sonda olmama durumu
        gecici1=imlec;
        if(gecici1->sonraki==son){
            son->onceki=NULL;
            imlec->sonraki=NULL;
            son=imlec;
            cumle_uzunluk--;
            sonraki_sayfa--;
        }
        else if(gecici1->sonraki!=NULL){
            gecici2=gecici1->sonraki;
            gecici3=gecici2->sonraki;
            gecici2->onceki=NULL;
            gecici2->sonraki=NULL;
            imlec->sonraki=gecici3;
            gecici3->onceki=imlec;
            cumle_uzunluk--;
            sonraki_sayfa--;
        }
    }
}

void Alt_Satira_Gec(){
    int i;
    int deger_son=10-(imlec_konum%10);
    if(ilk!=son)
    {
        gecici1=imlec->onceki;
        gecici1->enter_alt_satira_gecis=1;
    }
    for(i=0;i<deger_son;i++){
        Ekle(' ');
    }
    sonraki_sayfa+=9;
    enter_sayisi++;
}

void Shift_Eleman_Ekle(){

}
void Shift_Ayarlar(){

}
void Ctrl_A(){
    secim_karakter=cumle_uzunluk;
    ctrlA_tiklama=1;
}

void Ctrl_Kopyala(){
    Eleman_Secim_Sira();
    int eleman_sayisi=0,i=0;
    if(ctrlA_tiklama==1){
        eleman_sayisi=cumle_uzunluk;
        shift_eleman_sayisi=eleman_sayisi;
        char dizi[eleman_sayisi];
        gecici1=ilk;
        while(gecici1!=son->sonraki){
            if(gecici1!=imlec){
                shift_dizi_cumle[i]=gecici1->deger;
                i++;
            }
            gecici1=gecici1->sonraki;
        }
    }
    else if(shift_konum>imlec_konum){
        if(shift_konum==cumle_uzunluk){
            eleman_sayisi=cumle_uzunluk-imlec_konum;
            shift_eleman_sayisi=eleman_sayisi;
            char dizi[eleman_sayisi];
            gecici1=imlec->sonraki;
            while(gecici1!=son->sonraki){
                shift_dizi_cumle[i]=gecici1->deger;
                i++;
                gecici1=gecici1->sonraki;
            }
        }
        else{
            int sayac=imlec_konum;
            eleman_sayisi=shift_konum-imlec_konum;
            shift_eleman_sayisi=eleman_sayisi;
            char dizi[eleman_sayisi];
            gecici1=imlec->sonraki;
            while(sayac!=shift_konum){
                shift_dizi_cumle[i]=gecici1->deger;
                i++;
                gecici1=gecici1->sonraki;
                sayac++;
            }
        }
    }
    else if(shift_konum<imlec_konum){
        if(shift_konum==0){
            eleman_sayisi=imlec_konum;
            shift_eleman_sayisi=eleman_sayisi;
            char dizi[eleman_sayisi];
            gecici1=ilk;
            while(gecici1!=imlec){
                shift_dizi_cumle[i]=gecici1->deger;
                i++;
                gecici1=gecici1->sonraki;
            }
        }
        else{
            int sayac=imlec_konum;
            eleman_sayisi=imlec_konum-shift_konum;
            shift_eleman_sayisi=eleman_sayisi;
            i=eleman_sayisi-1;
            char dizi[eleman_sayisi];
            gecici1=imlec->onceki;
            while(sayac!=shift_konum){
                shift_dizi_cumle[i]=gecici1->deger;
                i--;
                gecici1=gecici1->onceki;
                sayac--;
            }
        }
    }
}
void Eleman_Secim_Sira(){
    ///BU FONKSIYON; KONSOLDA YILDIZLAR ARASINDA YAZAN, KESME VE KOPYALAMA ISLEMLERINDE SECILENLENRI GOSTEREN KARAKTERLERDEN KAC TANE GOSTERILECEGINI
    ///secim_karakter DEGISKENINE AKTARIR...
    if(shift_konum<imlec_konum){
        secim_karakter=imlec_konum-shift_konum;
    }
    else if(shift_konum>imlec_konum){
        secim_karakter=shift_konum-imlec_konum;
    }
}
void Ctrl_Kes(){
    Eleman_Secim_Sira();
    int eleman_sayisi=0,i=0,j=0;
    if(ctrlA_tiklama==1){
        eleman_sayisi=cumle_uzunluk;
        shift_eleman_sayisi=eleman_sayisi;
        char dizi[eleman_sayisi];
        gecici1=ilk;
        while(gecici1!=son->sonraki){
            if(gecici1!=imlec){
                shift_dizi_cumle[i]=gecici1->deger;
                i++;
            }
            gecici1=gecici1->sonraki;
        }
        ilk->sonraki=NULL;
        ilk->onceki=NULL;
        son->sonraki=NULL;
        son->onceki=NULL;
        imlec->sonraki=NULL;
        imlec->onceki=NULL;
        ilk=imlec;
        son=ilk;
        cumle_uzunluk=0;
        imlec_konum=0;
        sonraki_sayfa=0;
    }
    else if(shift_konum>imlec_konum){
        if(shift_konum==cumle_uzunluk){
            eleman_sayisi=cumle_uzunluk-imlec_konum;
            shift_eleman_sayisi=eleman_sayisi;
            char dizi[eleman_sayisi];
            gecici1=imlec->sonraki;
            while(gecici1!=son->sonraki){
                shift_dizi_cumle[i]=gecici1->deger;
                i++;
                gecici1=gecici1->sonraki;
            }
            gecici1=imlec->sonraki;
            gecici1->onceki=NULL;
            imlec->sonraki=NULL;
            son=imlec;
            cumle_uzunluk-=eleman_sayisi;
            sonraki_sayfa-=eleman_sayisi;
        }
        else{
            int sayac=imlec_konum;
            eleman_sayisi=shift_konum-imlec_konum;
            shift_eleman_sayisi=eleman_sayisi;
            char dizi[eleman_sayisi];
            gecici1=imlec->sonraki;
            while(sayac!=shift_konum){
                shift_dizi_cumle[i]=gecici1->deger;
                i++;
                gecici1=gecici1->sonraki;
                sayac++;
            }
            gecici2=gecici1->onceki;
            gecici3=imlec->sonraki;
            gecici3->onceki=NULL;
            gecici2->sonraki=NULL;
            imlec->sonraki=gecici1;
            gecici1->onceki=imlec;
            cumle_uzunluk-=eleman_sayisi;
            sonraki_sayfa-=eleman_sayisi;
        }
    }
    else if(shift_konum<imlec_konum){
        if(shift_konum==0){
            eleman_sayisi=imlec_konum;
            shift_eleman_sayisi=eleman_sayisi;
            char dizi[eleman_sayisi];
            gecici1=ilk;
            while(gecici1!=imlec){
                shift_dizi_cumle[i]=gecici1->deger;
                i++;
                gecici1=gecici1->sonraki;
            }
            gecici2=imlec->onceki;
            gecici2->sonraki=NULL;
            imlec->onceki=NULL;
            ilk=imlec;
            cumle_uzunluk-=eleman_sayisi;
            imlec_konum-=eleman_sayisi;
            sonraki_sayfa-=eleman_sayisi;
        }
        else{
            int sayac=imlec_konum;
            eleman_sayisi=imlec_konum-shift_konum;
            shift_eleman_sayisi=eleman_sayisi;
            i=eleman_sayisi-1;
            char dizi[eleman_sayisi];
            gecici1=imlec->onceki;
            while(sayac!=shift_konum){
                shift_dizi_cumle[i]=gecici1->deger;
                i--;
                gecici1=gecici1->onceki;
                sayac--;
            }
            gecici2=gecici1->sonraki;
            gecici3=imlec->onceki;
            gecici3->sonraki=NULL;
            gecici2->onceki=NULL;
            imlec->onceki=gecici1;
            gecici1->sonraki=imlec;
            cumle_uzunluk-=eleman_sayisi;
            imlec_konum-=eleman_sayisi;
            sonraki_sayfa-=eleman_sayisi;
        }
    }
}
void Ctrl_Yapistir(){
    int i;
    if(imlec==ilk){
        for(i=0;i<shift_eleman_sayisi;i++){
            if(i==0){
                gecici3=malloc(sizeof(struct Kayit));
                gecici3->deger=shift_dizi_cumle[i];
                gecici3->enter_alt_satira_gecis=0;
                gecici3->onceki=NULL;
                gecici3->sonraki=imlec;
                imlec->onceki=gecici3;
                ilk=gecici3;
                imlec_konum+=1;
                cumle_uzunluk+=1;
                sonraki_sayfa+=1;
            }
            else{
                gecici2=imlec->onceki;
                gecici3=malloc(sizeof(struct Kayit));
                gecici3->onceki=gecici2;
                gecici3->deger=shift_dizi_cumle[i];
                gecici3->enter_alt_satira_gecis=0;
                gecici3->sonraki=imlec;
                imlec->onceki=gecici3;
                gecici2->sonraki=gecici3;
                imlec_konum+=1;
                cumle_uzunluk+=1;
                sonraki_sayfa+=1;
            }
        }
    }
    else if(imlec==son){
        for(i=0;i<shift_eleman_sayisi;i++){
            gecici1=imlec;
            gecici2=imlec->onceki;
            gecici3=malloc(sizeof(struct Kayit));
            gecici3->deger=shift_dizi_cumle[i];
            gecici3->enter_alt_satira_gecis=0;
            gecici3->sonraki=imlec;
            gecici3->onceki=gecici2;
            imlec->onceki=gecici3;
            gecici2->sonraki=gecici3;
            son=imlec;
        }
        imlec_konum+=shift_eleman_sayisi;
        cumle_uzunluk+=shift_eleman_sayisi;
        sonraki_sayfa+=shift_eleman_sayisi;
    }
    else{
        for(i=0;i<shift_eleman_sayisi;i++){
            gecici1=imlec;
            gecici2=imlec->onceki;
            gecici3=malloc(sizeof(struct Kayit));
            gecici3->deger=shift_dizi_cumle[i];
            gecici3->enter_alt_satira_gecis=0;
            gecici3->sonraki=imlec;
            gecici3->onceki=gecici2;
            imlec->onceki=gecici3;
            gecici2->sonraki=gecici3;
        }
        imlec_konum+=shift_eleman_sayisi;
        cumle_uzunluk+=shift_eleman_sayisi;
        sonraki_sayfa+=shift_eleman_sayisi;
    }
}
void Anasayfa(){
    int kontrol=1;
    int sayi=0;
    char karakter;
    while(kontrol){
        system("CLS");
        Menu_Yazdir();
        scanf("%c",&karakter);
        if(karakter=='1'){
            kontrol=0;
        }
        else if(karakter=='2'){
            Kayit_Ac_2();
            kontrol=0;
        }
        else if(karakter=='3'){
            Kayit_Sil();
            kontrol=0;
        }
        else if(karakter=='4'){
            exit(0);
            kontrol=0;
        }
        else{
            kontrol=1;
        }
    }
}
void Menu_Yazdir(){
    printf("\n\t  MENU");
    printf("\n\t  -------------");
    printf("\n\t  1.YENI SAYFA");
    printf("\n\t  2.KAYIT AC");
    printf("\n\t  3.KAYIT SIL");
    printf("\n\t  4.CIKIS\n");
    printf("\n\t  Seciminiz : ");
}

void Bilgilendirme(){
    system("cls");
    printf("\n\t  BINLGILENDIRME-KISAYOL TUSLARI");
    printf("\n\t  -------------------------------");
    printf("\n\t  F1 : ANAMENU");
    printf("\n\t  CTRL+A : TUM ELEMANLARI SECME");
    printf("\n\t  CTRL+X : KES");
    printf("\n\t  CTRL+C : KOPYALA");
    printf("\n\t  CTRL+V : YAPISTIR");
    printf("\n\t  Imleci");
    printf("\n\t  1 -> Sol");
    printf("\n\t  3 -> Sag");
    printf("\n\t  5 -> Yukari");
    printf("\n\t  2 -> Asagi");
    printf("\n\t  Tuslariyla Hareket Ettirebilirsiniz.");
    printf("\n\t  Yon tuslari ile imleci sag-sol-asagi-yukari hareket ettirebilirsiniz.");
    printf("\n\t  ESC : CIKIS");
    printf("\n\t  Devam etmek icin herhangi bir harfe basabilirsiniz...");
    getch();
}


void Kayit(){
    system("CLS");
    FILE *fp;
    char dosya_adi[30];
    printf("\n\tDosya adi : ");
    scanf("%s",&dosya_adi);
    strcat(dosya_adi,".txt");
    fp=fopen(dosya_adi,"w+");
    gecici1=ilk;
    while(gecici1->sonraki!=NULL){
        if(gecici1!=imlec){
            fprintf(fp,"%c",gecici1->deger);
        }
        gecici1=gecici1->sonraki;
    }
    fclose(fp);
    printf("\n\tKaydedildi");
    printf("\n\tDevam etmek icin bir harfe basin.");
    getch();
}

void Kayit_Ac(){
    ilk=NULL;
    son=NULL;
    Baslangic_Ayar();
    system("cls");

    char dosya_adi[30];
    int sayac=0;
    printf("\n\tDosya adi : ");
    scanf("%s",&dosya_adi);
    strcat(dosya_adi,".txt");
    fp=fopen(dosya_adi,"ab+");
    if(fp==NULL){
        printf("\n\tDosya Bulunamadi.");
        fclose(fp);
    }
    else{
        while(!feof(fp)){
            Ekle(getc(fp));
        }
        fclose(fp);
    }
}

void Kayit_Ac_2(){
    system("cls");
    char dosya_adi[30];
    int sayac=0;
    printf("Dosya adi : ");
    scanf("%s",&dosya_adi);
    strcat(dosya_adi,".txt");
    fp=fopen(dosya_adi,"ab+");
    if(fp==NULL){
        printf("\n\tDosya Bulunamadi.");
        fclose(fp);
    }
    else{
        while(!feof(fp)){
            Ekle(getc(fp));
        }
        fclose(fp);
    }
}
void Kayit_Sil(){
    system("CLS");
    char dosya_adi[30];
    int sayac=0;
    printf("\n\tDosya adi : ");
    scanf("%s",&dosya_adi);
    strcat(dosya_adi,".txt");
    fp=fopen(dosya_adi,"r");
    if(fp==NULL){
        printf("\n\tDosya Bulunamadi.");
    }
    else{
        remove(dosya_adi);
        printf("\n\tKayit silindi...");
    }
    printf("\n\tDevam etmek icin bir harfe basin.");
    getch();
    Anasayfa();
    fclose(fp);
}
