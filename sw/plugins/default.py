from hexdump import hexdump
# 
# pip install hexdump
#

def send_data(data):
    print "Send: ({}):".format(len(data))
    hexdump(data)
    return data


def receive_data(data):
    print "Recv: ({}):".format(len(data))
    hexdump(data)
    return data
