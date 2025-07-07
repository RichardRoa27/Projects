import hashlib


#file_path = "\OneDrive\modified_alice.txt"
def generate_and_save_key(filename):
    # Generate a random 32-byte key
    secret_key = "12345"  # You can change this to any 5-character key
    with open(filename, 'w') as f:
        f.write(secret_key)

# Function to load the secret key from a file
def load_key(filename):
    with open(filename, 'r') as f:
        secret_key = f.read().strip()  # Remove leading/trailing whitespace
    return secret_key
key_file = 'secret_key.txt'

# Check if the key file exists
try:
    # Try to load the key from the file
    loaded_key = load_key(key_file)
    print("Loaded Secret Key:", loaded_key)
except FileNotFoundError:
    # If the file doesn't exist, generate a new key and save it
    print("Generating and saving a new secret key...")
    generate_and_save_key(key_file)
    print("Secret key saved to", key_file)
with open(file_path,"rb") as file:
    file_contents=file.read()
    hash=hashlib.sha256(file_contents).hexdigest()
hash_path= "secret_key.txt"
with open(hash_path,"w") as hash_path:
    hash_path.write(file_path)

print("file hash and key has being saved to ",hash_path)