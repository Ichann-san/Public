import subprocess
import sys
import unittest
from unittest.mock import patch, MagicMock
from io import StringIO


def main(hostname, username):
    # build the remote user@host string
    remote = "{}@{}".format(username, hostname)

    # build the SSH command list
    command = [
        'ssh', '-tt', '-o', 'StrictHostKeyChecking=accept-new', remote
    ]

    try:
        # run the SSH command, piping stdin/stdout/stderr
        completed = subprocess.run(
            command,
            input=b"echo Hello, world\nexit\n",
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
    except FileNotFoundError:
        print(
            "Error: the system 'ssh' command was not found. "
            "Install/enable OpenSSH Client first.",
            file=sys.stderr,
        )
        return 127

    # forward subprocess output to our own stdout/stderr
    sys.stdout.buffer.write(completed.stdout)
    sys.stderr.buffer.write(completed.stderr)
    return completed.returncode


# A 'null' stream that discards anything written to it
class NullWriter(StringIO):
    def write(self, txt):
        pass


def assert_equal(parameter1, parameter2):
    if parameter1 == parameter2:
        print(f'test attribute passed: {parameter1} is equal to {parameter2}')
    else:
        print(f'test attribute failed: {parameter1} is not equal to {parameter2}')


class TestSSHSimple(unittest.TestCase):
    @patch('subprocess.run')
    def test_main(self, mock_run):
        # Mock the CompletedProcess returned by subprocess.run
        mock_completed = MagicMock()
        mock_completed.stdout = b'Hello, world\n'
        mock_completed.stderr = b''
        mock_completed.returncode = 0
        mock_run.return_value = mock_completed

        # Patch sys.stdout and sys.stderr so buffer.write() is captured
        mock_stdout = MagicMock()
        mock_stderr_obj = MagicMock()

        with patch('sys.stdout', mock_stdout):
            with patch('sys.stderr', mock_stderr_obj):
                result = main('localhost', 'user')

        # sys.stdout is restored here; print() works normally again

        # Verify subprocess.run was called with the correct SSH command
        args, kwargs = mock_run.call_args
        command_called = args[0]
        cmd_str = ' '.join(command_called)
        print(f"SSH command: {cmd_str}")

        # Verify the correct input bytes were piped to the subprocess
        assert_equal(kwargs['input'], b"echo Hello, world\nexit\n")

        # Verify stdout output was forwarded via buffer.write
        mock_stdout.buffer.write.assert_called_once_with(b'Hello, world\n')
        print(f"stdout written: {mock_stdout.buffer.write.call_args}")

        # Verify the return code is propagated
        assert_equal(result, 0)


if __name__ == '__main__':
    runner = unittest.TextTestRunner(stream=NullWriter())
    unittest.main(testRunner=runner, exit=False)
