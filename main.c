#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>
#include <unistd.h>
//Gerekli olan kütüphaneleri ekledik.
//okunacakDosya dosyasının içeriği dolu. Bizim bu okunacakDosya dosyasını açıp okumamız ve içeriğini kopyalamamız gerekiyor.

void main()
{
  int sourceFd , targetFd; 
//Kaynak dosyanın file descriptırı var ve hedef dosyanın file descriptırı var. Bunlar open ve read de kullandığımız değerler.
  char buffer[100]; 
//Burda buffer’a yani bellekte bir alana ihtiyacımız var.Char tipinde olan.şimdilik 100 olsun.
  char sourceFileName[30], targetFileName[30];
  ssize_t readedVal, writedVal;

  

  printf("Kaynak dosyanın adını giriniz:"); //Kullanıcadan kaynak dosyanın ismini alıyoruz.
  scanf("%s", &sourceFileName);
//scanf ile girilen değeri okuyoruz
  printf("Hedef dosyanın adını giriniz:");
//burada da kullanıcıdan hedef dosyanın ismini alıyoruz
  scanf("%s", &targetFileName);
//tekrar scanf diyerek girilen bu değeri okuyoruz

  sourceFd = open(sourceFileName, O_RDONLY);

//dosyayı açıyoruz.
//İlk parametre olarak kaynak dosyanın adını ve ikinci parametre olarakta sadece okuma modunda açılmasını sağlıyoruz.
// Eğer bu dosya açılırken negatif değer dönerse bu dosya açılamamıştır.
//Bu durumu da if içerisine koyarak kontrol ettiriyoruz.
  if(sourceFd < 0)
  {
    printf("Kaynak dosya açılamadı.\n");
    return 2;
  }


//Burada ise ilk parametre olarak hedef dosyanın ismini
//2.parametreler olarakta eğer bu dosya varsa üzerine yazılmasını yoksa yeniden yaratılmasını söylüyoruz.
//3. Parametre olarakta dosya yoksa hangi yetkiler ile oluşturulacagını veriyoruz.
//Eğer negatif dönerse hedef dosyanın açılma durumunu if yapısına sokarak kontrol ediyoruz.
  targetFd = open(targetFileName, O_WRONLY | O_CREAT, 0644);
  if(targetFd < 0)
  {
    printf("Hedef dosya açılamadı.\n");
    return 3;
  }

//burada ise okuma başarılı olduğu sürece kaynak dosyadan hedef dosyaya yazdırmasını sağlıyoruz.
//Bazı durumlarda okunan ile yazılan karakter sayısı aynı olmayabilir. Bununda konrolünü yazılan değer ile okunan değer eşitmi diye if yapsında kontrol ettiriyoruz.
  while ( (readedVal = read(sourceFd, &buffer, 100)) > 0  )
  {
    writedVal = write(targetFd, &buffer, (ssize_t)readedVal );
    if(writedVal != readedVal)
    {
      printf("Okunan ve yazılına değerler eşleşmedi.\n Exited : 1");
      return 1;
    }
  }

  close(sourceFd);
  close(targetFd);

//Dosyaları kapatmayı unutmuyoruz.
  printf("Kopyalama işlemi tamamlandı.\n");
//Ardından kullanıcıya mesaj vererek işlemin tamamlandığını haber veriyoruz.
  return 0;
}