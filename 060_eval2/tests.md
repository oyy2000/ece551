STEP1:
main():
### argc!=2
valgrind ./story-step1 
### fopen
valgrind ./story-step1
### fclose

### "__"(two underscores)
valgrind ./story-step1 testcases/story1__.txt
### "_"(one underscore)
valgrind ./story-step1 testcases/story1_.txt
### "_:_"
valgrind ./story-step1 testcases/story1_:_.txt

STEP2:
main():
argc!=2
fopen
fclose

story.txt:
### ::B 
valgrind ./story-step2 testcases/words2::B.txt
### A B
valgrind ./story-step2 testcases/words2A_B.txt
### A:
valgrind ./story-step2 testcases/words2A:.txt

STEP3:
main():
argc!=3
fopen
### fclose
valgrind  --leak-check=full --show-leak-kinds=all ./story-step3 testcases/words3InvalidNumber.txt testcases/story3InvalidNumber-1.txt

story.txt:
### invalid number (-1, 0, 1000)
valgrind  --leak-check=full --show-leak-kinds=all ./story-step3 testcases/words3InvalidNumber.txt testcases/story3InvalidNumber-1.txt

valgrind  --leak-check=full --show-leak-kinds=all ./story-step3 testcases/words3InvalidNumber.txt testcases/story3InvalidNumber0.txt

valgrind  --leak-check=full --show-leak-kinds=all ./story-step3 testcases/words3InvalidNumber.txt testcases/story3InvalidNumber1000.txt

invalid character: requested category does not exist in"cats"
valgrind  --leak-check=full --show-leak-kinds=all ./story-step3 testcases/words3InvalidNumber.txt testcases/story3NotExist.txt 

STEP4:
main():
### argc!=(3||4)
valgrind  --leak-check=full --show-leak-kinds=all ./story-step4 -n testcases/words3InvalidNumber.txt testcases/story3NotExist.txt 


fopen
fclose

story.txt:

### invalid number (-1, 0, 1000)
valgrind  --leak-check=full --show-leak-kinds=all ./story-step4 testcases/words4InvalidNumber.txt testcases/story4InvalidNumber-1.txt
valgrind  --leak-check=full --show-leak-kinds=all ./story-step4 -n testcases/words4InvalidNumber.txt testcases/story4InvalidNumber-1.txt
valgrind  --leak-check=full --show-leak-kinds=all ./story-step4 testcases/words4InvalidNumber.txt testcases/story4InvalidNumber0.txt

valgrind  --leak-check=full --show-leak-kinds=all ./story-step4 testcases/words4InvalidNumber.txt testcases/story4InvalidNumber1000.txt
### invalid character: requested category does not exist in"cats"

### the category does not have any words
valgrind  --leak-check=full --show-leak-kinds=all ./story-step4 -n testcases/words4NULL.txt testcases/story4InvalidNumber-1.txt

### words used out

valgrind  --leak-check=full --show-leak-kinds=all ./story-step4 -n testcases/words4InvalidNumber.txt testcases/story4UsedOut.txt
### wrong -n
valgrind  --leak-check=full --show-leak-kinds=all ./story-step4 -nn testcases/words4InvalidNumber.txt testcases/story4InvalidNumber-1.txt

./story-step1 testcases/story1.txt
story-step1 bogusstory.txt

story-step2 words.txt
story-step2 mytrickywords.txt

story-step3 words.txt story.txt
story-step3 words.txt mystory1.txt
story-step3 trickywords.txt trickystory.txt

story-step4 words.txt story.txt
story-step4 words.txt mystory1.txt
story-step4 trickywords.txt trickystory.txt
story-step4 -n words.txt story.txt
story-step4 -n words.txt mystory1.txt
story-step4 -n trickywords.txt trickystory.txt

#Unable to open the file!