
import numpy

CAND = 0  # subscript of list which represents the candidate
SCORE = 1  # subscript of list which represents the score of the candidate
PLACE = 2  # subscript of list which represents the ranking, lowest is best

def tallyVotes(candidates, ordered, eliminated):
    tally = {c: 0 for c in range(1, candidates + 1)}
    for vote in ordered:
        # find first non-eliminated candidate in that ranked vote
        for candidate in vote:
            if candidate not in eliminated:
                tally[candidate] += 1
                break
    print(tally)
    return tally


def ranked_winner(names, voters, candidates, ordered):
    # pass in all the voters and rankings
    # iterate through the rankings and keep track of votes to each (list?)
    # only look at first choice unless there is a tie, then count up last choices for those two
    # for the loser, remove that first option
    # count through again until there is one left
    print("\nRanked choice voting:")
    eliminated =[]
    while True:
        tally = tallyVotes(candidates, ordered, eliminated)
        remaining = {c: v for c, v in tally.items() if c not in eliminated}
        lowest_candidate = min(remaining, key=remaining.get)
        print(f"Candidate {lowest_candidate} is eliminated")
        eliminated.append(lowest_candidate)
        if len(remaining) == 1:
            winner = next(iter(remaining.keys()))
            print(f"Winner is candidate {winner}\n")
            return winner
        

def social_welfare(names, ranking, voters, winner):
    cTotal = 0
    oTotal = 0

    for i in range(voters):
        name = names[i]

        for cand, score, rank in ranking[i]:
            if rank == 1:
                firstScore = score
                firstRank = rank

            if cand == winner:
                winnerRank = rank
                winnerScore = score

        cUtility= abs(round(firstScore-winnerScore, 2))
        oUtility = abs(firstRank-winnerRank)
        cTotal+=cUtility
        oTotal += oUtility

        print(f'{name}utility: {cUtility}, {oUtility} ')

    print(f'Social Welfare (Cardinal Utility): {round(cTotal,2)}')
    print(f'Social Welfare (Ordinal Utility): {oTotal}')


def print_connections(names, c, voters, candidates):
    print("CONNECTIONS")
    for i in range(voters):
        print("%10s" % (names[i]), end=" ")
        for j in range(voters):
            print(c[i][j], end=' ')
        print()


def print_rankings(names, r, voters, candidates, ordered):
    print("CANDIDATE Rankings")
    for i in range(voters):
        #print("First choice for {} is {}".format(names[i], ordered[i][CAND]), end=" ")
        print(names[i], end=" ")
        for j in range(candidates):
            print(r[i][j], end='')
        print(" ORDER ", ordered[i])


def create_voting(voters, candidates):
    names = ["Alice ", "Bart  ", "Cindy ", "Darin ", "Elmer ", "Finn  ", "Greg  ", "Hank  ", "Ian   ", "Jim   ",
             "Kate  ", "Linc  ", "Mary  ", "Nancy ", "Owen  ", "Peter ", "Quinn ", "Ross  ", "Sandy ", "Tom   ",
             "Ursula", "Van   ", "Wendy ", "Xavier", "Yan   ", "Zach  "]

    connections = [[0 for i in range(voters)] for j in range(voters)]
    ordered = [[] for i in range(voters)]
    numpy.random.seed(1052)
    for i in range(voters):
        conn = round(numpy.random.uniform(0, voters / 2))
        for j in range(conn):
            connectTo = numpy.random.randint(0, voters)
            if (connectTo!=i):
                connections[i][connectTo] = 1
    print_connections(names, connections, voters, candidates)
    candidateRanking = [[list() for i in range(candidates)] for j in range(voters)]
    for i in range(voters):
        for j in range(candidates):
            candidateRanking[i][j] = [j + 1, round(numpy.random.uniform(0, 100)) / 10, 0]
        # print(candidateRanking[i])
        s = sorted(candidateRanking[i], reverse=True, key=lambda v: v[SCORE])
        ordered[i] = [s[i][CAND] for i in range(candidates)]
        for v in range(candidates):
            candidate = s[v][CAND] - 1  # which candidate has rank v+1
            candidateRanking[i][candidate][PLACE] = v + 1
    print_rankings(names, candidateRanking, voters, candidates, ordered)
    winner = ranked_winner(names, voters, candidates, ordered)
    social_welfare(names, candidateRanking, voters, winner)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    create_voting(20, 5)

# See PyCharm help at https://www.jetbrains.com/help/pycharm/

# Python code to demonstrate namedtuple()
