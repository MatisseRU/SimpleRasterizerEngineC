# How do I contribute properly ?
## Setting up a fork
Before you clone any repo and address pull requests, please, fork this repository to your GitHub account and then clone the fork.

## Setting up Origin and upstream
If you want to contribute properly without breaking all of the project's history, you must setup an "upstream" git variable for fetching and pushing changes.

Simply create the upstream variable by doing:  
`git remote add upstream https://github.com/MatisseRU/SimpleRasterizerEngineC`

Then move to your fork's master branch:
`git checkout master`

## Contributing
Now that you have cloned your fork and added the "upstream" variable, i'll show you the best practices when contributing to GitHub projects.

### fetching new modifications from the project's repository
Before you work on anything and do any modifications, you must get the most recent commits from the official repository:  
`git pull --rebase upstream master`  
or  
`git fetch upstream`  
`git rebase upstream/master`

### After having done modifications localy, add ; commit and push
When you've done your modifications on the local version of the project, you may want to open a **pull request** which informs me, the manager of the project, that you've done modifications and want to merge your modifications with the upstream repo (the project's public repository).

Before pushing to master, you **ABSOLUTELY MUST *REBASE* WITH THE UPSTREAM REPO**:  
`git fetch upstream`  
`git rebase upstream/master`

and then you can:  
`git push upstream`

**NEVER EVER FORCE-PUSH...**

### Commit conventions...
Please, when you make changes, make 1 commit per file/change.

Do not commit multiple unrelated changes in the same commit:  
`git add file1.c`  
`git commit -m "Added feature blabla to read_str_from_file_blablabla() located in file1.c"`

Also, use English. Even though you're terrible at English speaking/writing, don't worry, I am too :).