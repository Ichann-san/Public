import poplib
import unittest
import sys
from unittest.mock import patch, MagicMock
from io import StringIO

GOOGLE_POP3_SERVER = 'pop.googlemail.com'


def download_email(username):
    # connect to Google POP3 SSL server
    mailbox = poplib.POP3_SSL(GOOGLE_POP3_SERVER, '995')

    # authenticate with username and password
    mailbox.user(username)
    password = 'secret123'
    mailbox.pass_(password)

    # retrieve the total number of messages
    num_messages = len(mailbox.list()[1])
    print("Total emails: %s" % num_messages)
    print("Getting last message")

    # print every line of the last message
    for msg in mailbox.retr(num_messages)[1]:
        print(msg)

    # close the connection
    mailbox.quit()


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestDownloadEmail(unittest.TestCase):
    @patch('poplib.POP3_SSL')
    def test_download_email(self, mock_pop3_ssl):
        # Mock the POP3_SSL instance
        mock_mailbox_instance = MagicMock()
        mock_pop3_ssl.return_value = mock_mailbox_instance

        # Mock list() to return 3 messages
        mock_mailbox_instance.list.return_value = (
            b'+OK',
            [b'1 1000', b'2 2000', b'3 3000'],
            18
        )

        # Mock retr() to return a sample message
        mock_mailbox_instance.retr.return_value = (
            b'+OK',
            [b'From: sender@example.com', b'Subject: Test Email', b'Hello from POP3!'],
            120
        )

        # Call the function to test
        username = 'testuser@gmail.com'
        download_email(username)

        # verify that POP3_SSL was called with the correct server and port
        mock_pop3_ssl.assert_called_with('pop.googlemail.com', '995')
        print(f"mock_pop3_ssl.call_args: {mock_pop3_ssl.call_args}")

        # verify user() was called with the correct username
        mock_mailbox_instance.user.assert_called_once_with('testuser@gmail.com')
        print(f"mock_mailbox_instance.user.call_args: {mock_mailbox_instance.user.call_args}")

        # verify pass_() was called with the correct password
        mock_mailbox_instance.pass_.assert_called_once_with('secret123')
        print(f"mock_mailbox_instance.pass_.call_args: {mock_mailbox_instance.pass_.call_args}")

        # verify quit() was called
        mock_mailbox_instance.quit.assert_called_once()

        # verify the call arguments for user and pass_
        args_user, _ = mock_mailbox_instance.user.call_args
        args_pass, _ = mock_mailbox_instance.pass_.call_args

        assert_equal(args_user[0], 'testuser@gmail.com')
        assert_equal(args_pass[0], 'secret123')


if __name__ == '__main__':
    if len(sys.argv) == 2 and sys.argv[1] == 'run':
        download_email('testuser@gmail.com')
    else:
        runner = unittest.TextTestRunner(stream=NullWriter())
        unittest.main(testRunner=runner, exit=False)
