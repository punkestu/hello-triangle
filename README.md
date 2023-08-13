# OPENGL
## Review
OpenGL adalah salah satu Graphic API pada komputer. OpenGL berguna sebagai interface untuk mengakses graphic card / processor. OpenGL hanya sebuah interface, sedangkan implementasinya ada pada masing-masing graphic card. Oleh karena itu terkadang ada beberapa fitur yang hanya bisa berjalan di graphic card tertentu. Namun karena OpenGL hanya interface, maka OpenGL bisa cross-platform dan kompatibilitasnya hanya akan tergantung pada graphic card yang digunakan.

## Alur Kerja
Cara kerja OpenGL adalah dengan mengambil alih surface dari sebuah window, sehingga semua hal yang berkaitan dengan render and draw akan dikendalikan oleh OpenGL. Cara untuk menanamkan OpenGL pada sebuah window dilakukan dengan mengambil konteks dari window tersebut dan menghubungkannya dengan OpenGL lalu kita bisa mengelola tampilannya dengan OpenGL.

## VAO, VBO, dan EBO
VBO adalah sebuah buffer yang kita gunakan untuk menyimpan semua komponen yang dimiliki oleh sebuah objek, mulai dari vertex posisi, vertex texture, vertex normal, dll. Untuk membuatnya kita hanya harus membuat sebuah array buffer menggunakan OpenGL dimana nanti kita akan mendapatkan pointer untuk mengakses buffer tersebut. Setelah membuat array buffer, kita bisa melakukan buffer kedalam array buffer tersebut dengan mengirimkan sebuah array dari data yang dibutuhkan, ukuran array tsb, tipe datanya, dll.

EBO mirip dengan VBO namun bedanya jika pada VBO kita menyimpan komponen objek, pada EBO kita menyimpan urutan penggunaan dari sebuah komponen. Misal kita memiliki 8 vertex untuk membuat sebuah kubus, kita bisa membuat urutan garis yang akan dibentuk dari vertex tersebut agar menjadi sebuah kubus. Contoh yang lain misal jika kita ingin mengasosiasikan sebuah titik dengan texture, kita dapat melakukan mapping pada vertex posisi tertentu akan mendapatkan vertex texture yang mana. Untuk membuatnya mirip dengan VBO hanya berbeda pada modenya saja.

VAO adalah bungkus dari VBO dan EBO dimana didalam VAO ini nantinya kita dapat mengelola VBO dan EBO. Misal membuat partisi pada komponen VBO agar data yang awalnya hanya array linear dapat dibaca secara struktural. Untuk membuatnya kita hanya perlu membuat vertex array dimana setelah kita bind kita dapat melakukan bind VBO dan EBO yang kita inginkan agar terbungkus dalam VAO ini.

## Shader
Shader akan mendeskripsikan bagaimana objek kita nanti akan dirender. Shader akan berisi program (GLSL jika pada OpenGL) yang akan menjelaskan runtutan cara merender objek. Pada OpenGL shader yang umum digunakan di awal adalah vertex dan fragment shader.

Vertex shader adalah shader yang bertugas untuk mengatur posisi vertex yang kita inputkan. Misal jika kita ingin melakukan rotation, scaling, moving, projection, dll maka kita melakukannya di vertex shader ini.

Fragment shader adalah shader yang bertugas untuk mengatur pewarnaan pada objek. Misal jika kita ingin mengatur pencahayaan pada objek kita, kita bisa melakukannya di vertex shader ini dengan bantuk beberapa vertex dan matrix misal vertex normal.
