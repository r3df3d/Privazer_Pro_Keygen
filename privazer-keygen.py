def generate_privaZer_license(email):
    """
    Generate a PrivaZer Pro license key from the given email address.
    
    :param email: str, the email address (e.g., "user@example.com")
    :return: str, the 10-digit license key
    """
    # Extract the local part of the email (before '@')
    try:
        prefix = email.split('@')[0]
    except IndexError:
        return "Invalid email format. Please provide a valid email address."

    license_digits = []

    # Process each character in the prefix
    for char in prefix:
        # Convert character to ASCII code and split into digits
        ascii_digits = list(str(ord(char)))
        license_digits.extend(ascii_digits)
        
        # Stop once we have 10 digits
        if len(license_digits) >= 10:
            break

    # Return the first 10 digits as the license key
    if len(license_digits) < 10:
        return "The email prefix is too short to generate a valid license key."
    
    return ''.join(license_digits[:10])


def main():
    print("=== PrivaZer Pro Keygen[by redfed] ===")
    print("Enter your email address to generate a license key.\n")

    while True:
        # Prompt the user for input
        email = input("Enter Email Address (or type 'exit' to quit): ").strip()

        # Exit condition
        if email.lower() == 'exit':
            print("\nThank you for using the PrivaZer Pro License Key Generator. Goodbye!")
            break

        # Validate email and generate license
        if "@" not in email or email.count("@") > 1:
            print("Error: Invalid email format. Please ensure the email contains a single '@'.\n")
            continue

        license_key = generate_privaZer_license(email)

        # Display the result
        print(f"\nEmail: {email}")
        print(f"License Key: {license_key}\n")


# Run the program
if __name__ == "__main__":
    main()