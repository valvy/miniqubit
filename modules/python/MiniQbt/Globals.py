import MiniQbtNative

def getVersion():
    '''
    Gets the version number of MiniQbt as string.
    '''
    return MiniQbtNative.get_version()

def getName():
    '''
    Gets the name of the used MiniQbt. (Mostly just MiniQbt)
    '''
    return MiniQbtNative.get_name()