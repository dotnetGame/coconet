import coconet

if __name__ == "__main__":
    a = coconet.FloatVariable([3,4])
    b = coconet.FloatVariable([4,3])
    print(a)
    a.fill_(1)
    print(a)