
import numpy
import random

CAND = 0  # subscript of list which represents the candidate
SCORE = 1  # subscript of list which represents the score of the candidate
PLACE = 2  # subscript of list which represents the ranking, lowest is best

def tallyVotes(candidates, ordered, eliminated):
    tally = {c: 0 for c in range(1, candidates + 1)}
    for vote in ordered:
        # find first non-eliminated candidate in that ranked vote and count
        for candidate in vote:
            if candidate not in eliminated:
                tally[candidate] += 1
                break
    print("\n")
    print(tally)
    return tally


def ranked_winner(candidates, ordered):
    # iterate through the rankings and eliminate least popular each round
    print("\nRanked choice voting:")
    eliminated = []
    while True:
        tally = tallyVotes(candidates, ordered, eliminated)
        remaining = {c: v for c, v in tally.items() if c not in eliminated}
        lowest_candidate = min(remaining, key=remaining.get)
        
        if len(remaining) == 1:
            winner = next(iter(remaining.keys()))
            print(f"Winner is candidate {winner}\n")
            return winner
        
        print(f"Candidate {lowest_candidate} is eliminated")
        eliminated.append(lowest_candidate)
        

def social_welfare(names, ranking, voters, winner):
    cTotal = 0
    oTotal = 0

    for i in range(voters):
        name = names[i]
        firstScore = 0
        firstRank = 0
        winnerRank = 0
        winnerScore = 0

        for cand, score, rank in ranking[i]:
            if rank == 1:
                firstScore = score
                firstRank = rank

            if cand == winner:
                winnerRank = rank
                winnerScore = score

        cUtility = abs(round(firstScore-winnerScore, 2))
        oUtility = abs(firstRank-winnerRank)
        cTotal += cUtility
        oTotal += oUtility

        print(f'{name}utility: {cUtility}, {oUtility} ')

    print(f'Social Welfare (Cardinal Utility): {round(cTotal, 2)}')
    print(f'Social Welfare (Ordinal Utility): {oTotal}')


def social_network(names, voters, candidates, connections, ordered):
    eliminated = []
    stay = .25

    print("\nSocial Network Voting:")

    tally = tallyVotes(candidates, ordered, eliminated)
    remaining = {c: v for c, v in tally.items() if c not in eliminated}
    lowest = min(remaining, key=remaining.get)
    print(f"Candidate {lowest} eliminated")
    eliminated.append(lowest)

    # social influence starts in round 2
    round_num = 2

    while True:
        print(f"\nROUND {round_num}:")

        # Track changes this round
        change_log = []

        for v in range(voters):
            ordered[v]= [c for c in ordered[v] if c not in eliminated]
            ballot = ordered[v]
            original_ballot = ballot[:]

            first = next((c for c in ballot if c not in eliminated), None)
            second = next((c for c in ballot if c not in eliminated and c != first), None)

            # check connections top choices
            neighbor_tops = []
            for nbr in range(voters):
                if connections[v][nbr] == 1:
                    for c in ordered[nbr]:
                        if c not in eliminated:
                            neighbor_tops.append(c)
                            break

            # if neighbors prefer your 2nd
            if second is not None:
                if neighbor_tops.count(second) > neighbor_tops.count(first):
                    new_ballot = [second] + [c for c in ballot if c != second and c not in eliminated]
                    if random.random() < stay:
                        print(f"  {names[v].strip():6s} was stubborn and keeps {ballot}")
                        continue

                    ordered[v] = new_ballot
                    change_log.append((names[v], original_ballot, new_ballot,
                                        "Neighbors prefer second choice"))
                    continue
            # else no change this round

        #print changes
        if change_log:
            print("\nVoter switches this round:")
            for name, old, new, reason in change_log:
                print(f"  {name.strip():6s} switched  {old}  ->  {new}   ({reason})")
        else:
            print("\nNo voters changed their minds this round.")

        tally = tallyVotes(candidates, ordered, eliminated)
        remaining = {c: v for c, v in tally.items() if c not in eliminated}

        # check for winner
        if len(remaining) == 1:
            winner = next(iter(remaining))
            print(f"\nWinner under Social Network: {winner}\n")
            return winner

        lowest = min(remaining, key=remaining.get)
        print(f"Candidate {lowest} eliminated")
        eliminated.append(lowest)

        round_num += 1
 


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
    winner = ranked_winner(candidates, ordered)
    social_welfare(names, candidateRanking, voters, winner)
    print_connections(names, connections, voters, candidates)
    socialWinner = social_network(names, voters, candidates, connections, ordered)
    social_welfare(names, candidateRanking, voters, socialWinner)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    create_voting(20, 5)

# See PyCharm help at https://www.jetbrains.com/help/pycharm/

# Python code to demonstrate namedtuple()
