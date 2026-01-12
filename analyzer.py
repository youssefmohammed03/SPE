import sys

def analyze_profile(filename):
    print(f"{'='*60}")
    print(f"{'EVENT LOG & CALL RELATIONSHIP REPORT':^60}")
    print(f"{'='*60}")
    print(f"{'Timestamp':<12} | {'Caller':<15} -> {'Callee':<15} | {'Event':<10}")
    print("-" * 60)

    try:
        with open(filename, 'r') as f:
            lines = f.readlines()
            
            for line in lines[1:]:
                parts = line.strip().split(',')
                if len(parts) < 4:
                    continue
                
                timestamp = parts[0]
                event = parts[1]
                func_name = parts[2]
                caller = parts[3]

                if event == "ENTER":
                    arrow = "->"
                    print(f"{timestamp:<12} | {caller:<15} {arrow} {func_name:<15} | START")
                elif event == "EXIT":
                    print(f"{timestamp:<12} | {func_name:<15} {'--':^4} {'END':<15} | END")

        print(f"{'='*60}")
        print("Analysis Complete. 'path_profile.txt' successfully processed.")

    except FileNotFoundError:
        print("Error: path_profile.txt not found. Run the C program first.")

if __name__ == "__main__":
    analyze_profile("path_profile.txt")