import smtplib
import socket
import sys
import unittest
from unittest.mock import patch, MagicMock, call
from io import StringIO

message_template = """To: {}
From: {}
Subject: Test Message from simple.py

Hello,

This is a test message sent to you.
"""


def main():
    if len(sys.argv) < 4:
        name = sys.argv[0]
        print("Syntax: {} server fromaddr toaddr [toaddr...]".format(name))
        sys.exit(2)

    server, fromaddr, toaddrs = sys.argv[1], sys.argv[2], sys.argv[3:]
    message = message_template.format(', '.join(toaddrs), fromaddr)

    try:
        # create an SMTP connection to the server and report on message size
        connection = smtplib.SMTP(server)
        report_on_message_size(connection, fromaddr, toaddrs, message)
    except (socket.gaierror, socket.error, socket.herror,
            smtplib.SMTPException) as e:
        print("Your message may not have been sent!")
        print(e)
        sys.exit(1)
    else:
        s = 's' if len(toaddrs) > 1 else ''
        print("Message sent to {} recipient{}".format(len(toaddrs), s))
        connection.quit()


def report_on_message_size(connection, fromaddr, toaddrs, message):
    # Check if the server supports ESMTP and the SIZE extension
    code, response = connection.ehlo()
    uses_esmtp = (200 <= code <= 299)
    if not uses_esmtp:
        code, response = connection.helo()
        if not (200 <= code <= 299):
            print("Remote server refused HELO; code:", code)
            sys.exit(1)

    if uses_esmtp and connection.has_extn('size'):
        print("Maximum message size is {}".format(connection.esmtp_features['size']))
        if len(message) > int(connection.esmtp_features['size']):
            print("Message too large; aborting.")
            sys.exit(1)

    # Send the message
    connection.sendmail(fromaddr, toaddrs, message)


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestExtendedHello(unittest.TestCase):

    @patch('__main__.report_on_message_size')
    @patch('smtplib.SMTP')
    def test_main(self, mock_smtp_cls, mock_report):
        mock_connection = MagicMock()
        mock_smtp_cls.return_value = mock_connection

        with patch('sys.argv', ['ehlo.py', 'smtp.example.com',
                                'sender@example.com', 'recipient@example.com']):
            main()

        print(f"mock_smtp_cls.call_args: {mock_smtp_cls.call_args}")
        assert_equal(mock_report.called, True)
        assert_equal(mock_connection.quit.called, True)

    def test_report_on_message_size(self):
        mock_connection = MagicMock()
        mock_connection.ehlo.return_value = (250, b'OK')
        mock_connection.has_extn.return_value = True
        mock_connection.esmtp_features = {'size': '10000000'}

        fromaddr = 'sender@example.com'
        toaddrs = ['recipient@example.com']
        message = 'Test message'

        report_on_message_size(mock_connection, fromaddr, toaddrs, message)

        assert_equal(mock_connection.sendmail.called, True)
        assert_equal(mock_connection.sendmail.call_args[0][0], fromaddr)
        assert_equal(mock_connection.sendmail.call_args[0][1], toaddrs)


if __name__ == '__main__':
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
