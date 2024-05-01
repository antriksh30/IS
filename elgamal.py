import random
    
def extended_gcd(aa, bb):
    lastremainder, remainder = abs(aa), abs(bb)
    x, lastx, y, lasty = 0, 1, 1, 0
    while remainder:
        lastremainder, (quotient, remainder) = remainder, divmod(lastremainder, remainder)
        x, lastx = lastx - quotient*x, x
        y, lasty = lasty - quotient*y, y
    return lastremainder, lastx * (-1 if aa < 0 else 1), lasty * (-1 if bb < 0 else 1)


#Euclid's extended algorithm for finding the multiplicative inverse of two numbers    
def modinv(a, m):
	g, x, y = extended_gcd(a, m)
	if g != 1:
		raise Exception('Modular inverse does not exist')
	return x % m    
 
def gcd(a,b):
    while b != 0:
        a, b = b, a % b
    return a


def primRoot(modulo):
    roots = []
    required_set = set(num for num in range (1, modulo) if gcd(num, modulo) == 1)
    
    for g in range(1, modulo):
        actual_set = set(pow(g, powers) % modulo for powers in range (1, modulo))
        if required_set == actual_set:
            roots.append(g)           
    return roots[0]
 

def egKey():
    p = 881
    g = primRoot(p)
    
    # privateKey = random.randint(1, p-2)
    privateKey = 700
    publicKey = pow(g,privateKey,p)
    return p, g, privateKey, publicKey


#  Signature Generation 

def egGen(p, e1, d, m):
    # while 1:
    #     r = random.randint(1,p-2)
    #     if gcd(r, p-1)==1: break
    r=17
    s1 = pow(e1,r,p)
    l = modinv(r, p-1)
    
    s2 = l*(m- d*s1)%(p-1) 
    return s1,s2

#  Signature Verification 
def egVer(p, e1, e2, s1, s2, m):
    if s1 < 1 or s1 > p-1 : return False
    if s2 < 1 or s2 >= p-1 : return False
    v1 = pow(e2,s1,p)%p * pow(s1,s2,p)%p
        
    v2 = pow(e1,m,p)


    isValid = v1==v2
    
    if isValid:
        print("Verification successful: ", )
        print(v1, " = ", v2)
    else:
        print("Verification failed:")
        print(v1, " != ", v2)
    
      
if __name__ == "__main__":
    m = 400
    print("Message: ", m)
    print()
    
    p, e1, d, e2 = egKey() 
    print("Public key (p, e1, e2): ", [p, e1, e2])
    print("Private key (d): ", d)
    
    print()
    rr,ss = egGen(p,e1,d, m)    
    print("Signature (s1, s2): ", rr, ss)
    
    print()
    egVer(p, e1, e2, rr, ss, m)