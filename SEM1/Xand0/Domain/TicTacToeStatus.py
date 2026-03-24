from Domain.TicTacToeGame import TicTacToeGame

class TicTacToeStatus:

    def __init__(self, game: TicTacToeGame, status, winner):
        self.__game = game
        self.__status = status
        self.__winner = winner

    def getGame(self):
        return self.__game

    def getStatus(self):
        return self.__status

    def getWinner(self):
        return self.__winner