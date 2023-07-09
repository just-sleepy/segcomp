from RSA import generateKey
from OAEP import oaepEncr, oaepDecr
import AES
import signaturefile

message = b"Num ninho de mafagafos ha sete mafagafinhos. Quando a mafagafa gafa, gafam os sete mafagafinhos."
print("Original message:", message)

########## PARTE 1 ##########
# geracao de chave de 128 bits
# cifracao e decifracao
# contador de Galois

aes = AES.AES()
aes_cif = aes.cipher(message)
aes_dec = aes.decipher(aes_cif)

print()
print("AES key:", aes.key)
print("AES ciphertext", aes_cif)
print("AES decrypted message:", aes_dec)
print()

########## PARTE 2 ##########
# geracao de chave do RSA testando primalidade com Miller-Rabin
# cifracao e decifracao assimetrica RSA utilizando OAEP

private_key, public_key = generateKey()
ciphertext = oaepEncr(message, public_key)
decrypted_message = oaepDecr(ciphertext, private_key)
print()
print("RSA private key:", private_key)
print("RSA public key: ", public_key)
print("RSA ciphertext:", ciphertext)
print("RSA decrypted message:", decrypted_message)
print()

########## PARTE 3 ##########
# assinatura da mensagem
# formatacao com base64

signature = signaturefile.signMessage(message, private_key)

print()
print("RSA signature: ", signature)
print()

########## PARTE 4 ##########
# verificacao

signature_flag = signaturefile.verifySignature(message, signature, public_key)
if signature_flag:
    print("Valid signature")
else:
    print("Invalid signature")

#############################

####### CASOS DE USO ########
message = b"O tempo perguntou ao tempo quanto tempo o tempo tem, o tempo respondeu ao tempo que o tempo tem o tempo que o tempo tem."
#1) M, k -> AES_k(M)
print()
#2) C = (AES_k(M) , RSA_KA_p(k))
print()
#3) C = (AES_k(M) , RSA_KB_s (RSA_KA_p(k)), KB_p) 
print()