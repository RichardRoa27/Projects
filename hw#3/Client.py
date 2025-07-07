from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Hash import SHA256
import bluetooth

def pad(data):
    """Pads the given data to make its length a multiple of AES block size."""
    return data + b"\x00" * (AES.block_size - len(data) % AES.block_size)

def encrypt_file(file_path, key):
    """Encrypts the file specified by file_path using AES encryption in EAX mode for both confidentiality and integrity."""
    cipher = AES.new(key, AES.MODE_EAX)
    with open(file_path, 'rb') as f:
        data = f.read()
    ciphertext, tag = cipher.encrypt_and_digest(pad(data))
    return ciphertext, tag, cipher.nonce

def send_file(sock, file_path):
    """Encrypts and sends a file over a Bluetooth connection, also returns a SHA-256 hash of the ciphertext."""
    key = get_random_bytes(16)  # Generate a random AES key
    ciphertext, tag, nonce = encrypt_file(file_path, key)

    # Send the encryption metadata and the encrypted data
    sock.send(nonce)
    sock.send(tag)
    sock.sendall(ciphertext)

    # Calculate and return the SHA-256 hash of the ciphertext
    hash_obj = SHA256.new()
    hash_obj.update(ciphertext)
    return hash_obj.digest(), key, nonce, tag

def main():
    """Main function to handle Bluetooth connection and file transfer."""
    target_addr = "B8:27:EB:F4:8D:F3"  # Target Bluetooth device address
    target_port = 1                    # RFCOMM port
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    sock.connect((target_addr, target_port))

    file_path = "/home/rroa/Downloads/alice.txt"
    try:
        file_hash, key, nonce, tag = send_file(sock, file_path)
        print("File sent, waiting for server confirmation and hash comparison...")

        # Receive the hash from the server and compare for integrity
        server_hash = sock.recv(1024)
        if server_hash == file_hash:
            print("File integrity verified successfully.")
        else:
            print("Warning: Data integrity could not be verified.")

        # Receive additional confirmation from the server
        server_confirmation = sock.recv(1024)
        print("Server confirmation:", server_confirmation.decode())
    except Exception as e:
        print("Error:", e)
    finally:
        sock.close()  # Ensure the socket is closed regardless of success or failure

if __name__ == "__main__":
    main()
