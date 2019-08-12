import coconet

class Test:
    def __init__(self):
        pass

    def __getitem__(self, key):
        print(key)

if __name__ == "__main__":
    a = coconet.FloatVariable([3,4])
    b = coconet.FloatVariable([4,3])
    a.fill_(1)
    print(a)

    Test()[2:3,4]