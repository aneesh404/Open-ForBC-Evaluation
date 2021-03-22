class Pattern:
    def __init__(self,filename):
        self.filename = filename 

    def print_common(self):
        try:
            with open(self.filename) as file:
                res_string = file.read()
        except FileNotFoundError as error:
            print(error)
        res_string = res_string[2:-2].split('", "')
        output = list(set(res_string[0].split(", ")).intersection(res_string[1].split(", ")))
        print(output)
        

def main():
    filename = "input.txt"
    ob1 = Pattern(filename)
    ob1.print_common()


if __name__ == '__main__':
    main()
    