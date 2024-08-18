'''
Basic Python Program Project
Author : Ariq Marwan Permana - 2024

'''


import os
import requests, json
url = 'https://v6.exchangerate-api.com/v6/33bad5a87409449068f37311/latest/USD'
response = requests.get(url)
BMI_i = 0

def convertCurrency(jsonText,sourceCurrCode, amount, destCurrCode):
	try:
		sRate = jsonText['conversion_rates'][sourceCurrCode]
		dRate = jsonText['conversion_rates'][destCurrCode]
		# convert from Source to some curr type
		x1 = amount / sRate
		# convert the result to destCurr
		x2 = x1 * dRate 
		return x2
	except:
		return -1

def BMI():
    global BMI_i
    if BMI_i == 1 :
        tanya4 = input("=> Apakah anda ingin menghitung BMI lagi? (Y/N) : ")
        if tanya4 == 'Y':
            os.system('cls')
        elif tanya4 == 'N':
            exp()
    else:
        os.system('cls')

    print('==================================')
    print('=         KALKULATOR BMI         =')
    print('==================================')
    umur = int(input("=> Masukkan umur         : "))
    kg = int(input("=> Masukkan berat badan  : "))
    tg = int(input("=> Masukkan tinggi badan : "))
    if umur >= 19 :
        i = i + 1
        x1 = tg/100
        hasil = kg/(x1*x1)
        float(hasil)
        os.system('cls')
        print("BMI Score : %.1f" %hasil)
        if hasil < 17.0 :
            print("Tergolong : Sangat Kurus")
            os.system('pause')
            BMI()
        elif hasil > 17 and hasil <= 18.4 : 
            print("Tergolong : Kurus") 
            os.system('pause')
            BMI()
        elif hasil >= 18.5 and hasil <= 25.0 :
            print("Tergolong : Normal")
            os.system('pause')
            BMI()
        elif hasil >= 25.1 and hasil <= 27.0 :
            print("Tergolong : Gemuk")
            os.system('pause')
            BMI()
        elif hasil > 27 :
            print("Tergolong : Obesitas")
            os.system('pause')
            BMI()
        else :
            print("=> Error : Perhitungan gagal!")
            os.system('pause')
            BMI() 
    else : 
        print("=> Maaf untuk umur dibawah 19 tahun masih dalam tahap pengembangan!")
        os.system('pause')
        BMI()

def exp():
    global BMI_i
    BMI_i = 0
    os.system('cls')
    print('==============================')
    print('=    EXPERIMENTAL FEATURE    =')
    print('==============================')
    print('= (1) Menghitung Diskon      =')
    print('= (2) Konversi Nilai Tukar   =')
    print('= (3) Kalkulator BMI         =')
    print('= (4) Menu Utama             =')
    print('==============================')
    tanya2 = input("Pilih opsi = ")
    if tanya2 == '1':
        x1 = int(input('Masukkan harga barang        = '))
        x2 = int(input('Masukkan jumlah barang       = '))
        x3 = int(input('Masukkan persenan diskon (%) = '))
        totbrg = x1*x2
        diskon = x3/100
        hasil  = totbrg - (diskon * totbrg)
        hasil1 = x1*diskon
        type(BMI_i)
        print("Total yang harus anda bayar adalah = %d" %hasil)
        print('Harga perbarang setelah diskon     = %d' %hasil1)
        os.system('pause')
        exp()
    elif tanya2 == '2':
        if (response.status_code== 200): 
            #if the response status code is 200 it's mean the server responded to your req
            #if the response status code is 400 it's mean the server not respond to your req
            jsonText = json.loads(response.text)
            # print(jsonText)
            if (jsonText['result']):
                sourceCurrCode = input("Dari Mata Uang : ")
                destCurrCode   = input("Ke Mata Uang   : ")
                amount = int(input("Input jumlah uang : "))
                result = convertCurrency(jsonText, sourceCurrCode, amount, destCurrCode)
                if result != -1:
                    print("Hasil konversi : %.1f %s ke %.1f %s" % (amount, sourceCurrCode, result, destCurrCode))
                    os.system('pause')
                    exp()
                else:
                    print("Konversi Mata Uang Gagal")
            else:
                print("Konversi Json Gagal")
        else:
            print("API Gagal")
    elif tanya2 == '3':
        BMI()
    elif tanya2 == '4':
        main()
    else:
        print('Pilihan tidak ditemukan!')
        exp()

def main():
    print('====================')
    print('=  SELAMAT DATANG  =')
    print('====================')
    print('= (1) Penambahan   =')
    print('= (2) Pengurangan  =')
    print('= (3) Pembagian    =')
    print('= (4) Perkalian    =')
    print('= (5) Keluar       =')
    print('====================')
    tanya1 = input("Pilih opsi = ")

    if tanya1 == '1':
        os.system('cls')
        print('= PENAMBAHAN =')
        x1 = int(input('=> Masukkan nilai pertama = '))
        x2 = int(input('=> Masukkan nilai kedua   = '))
        hasil = x1 + x2
        print("Hasilnya : %d" %hasil)
    elif tanya1 == '2' :
        os.system('cls')
        print('= PENGURANGAN =')
        x1 = int(input('=> Masukkan nilai pertama = '))
        x2 = int(input('=> Masukkan nilai kedua   = '))
        hasil = x1 - x2
        print("Hasilnya : %d" %hasil)
    elif tanya1 == '3' :
        os.system('cls')
        print('= PEMBAGIAN =')
        x1 = int(input('=> Masukkan nilai pertama = '))
        x2 = int(input('=> Masukkan nilai kedua   = '))
        hasil = x1/x2
        print("Hasilnya : %d" %hasil)
    elif tanya1 == '4':
        os.system('cls')
        print('= PERKALIAN =')
        x1 = int(input('=> Masukkan nilai pertama = '))
        x2 = int(input('=> Masukkan nilai kedua   = '))
        hasil = x1*x2
        print("Hasilnya : %d" %hasil)
    elif tanya1 == '5':
        exit(0)
    elif tanya1 == 'exp':
        exp()
    else : 
        os.system('cls')
        print("Pilihan tidak ada!")

#start the program from function "main"
main()
