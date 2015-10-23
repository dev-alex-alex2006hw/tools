project "libsec"
    -- is this kind of app
    kind "StaticLib"
    targetname "sec"
    buildoptions {"-fPIC"}
    includedirs{ "../include"}
    -- and is dependent on these files
    files { "des.c", "desmodes.c", "desECB.c", "desCBC.c", "des3ECB.c", "des3CBC.c", "aes.c", "blowfish.c", "idea.c", "hmac.c", "md5.c", "md5block.c",
        "md4.c", "sha1.c", "sha1block.c", "sha2.c", "sha256block.c", "sha512block.c", "sha1pickle.c", "md5pickle.c", "rc4.c", "genrandom.c", "prng.c",
        "fastrand.c", "nfastrand.c", "probably_prime.c", "smallprimetest.c", "genprime.c", "dsaprimes.c", "gensafeprime.c", "genstrongprime.c", 
        "rsagen.c", "rsafill.c", "rsaencrypt.c", "rsadecrypt.c", "rsaalloc.c", "rsaprivtopub.c", "eggen.c", "egencrypt.c", "egdecrypt.c",
        "egalloc.c", "egprivtopub.c", "egsign.c", "egverify.c", "dsagen.c", "dsaalloc.c", "dsaprivtopub.c", "dsasign.c", "dsaverify.c"}
  
