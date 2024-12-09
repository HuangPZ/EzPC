import re

def calculate_gpu_memory(filename):
    total_gpu_memory = 0  # Initialize total memory for GPU
    pattern = r"Moving (\d+) bytes to GPU memory"  # Regex pattern to extract memory values

    with open(filename, "r") as file:
        for line in file:
            match = re.search(pattern, line)  # Search for matching lines
            if match:
                memory = int(match.group(1))  # Extract the memory value in bytes
                total_gpu_memory += memory  # Add to the total

    return total_gpu_memory

# Replace 'input.txt' with the path to your text file
filename = "slurm-6208172.out"
total_memory = calculate_gpu_memory(filename)

# Print the result in bytes and megabytes
print(f"Total memory moved to GPU: {total_memory} bytes ({total_memory / (1024 * 1024):.2f} MB)")
