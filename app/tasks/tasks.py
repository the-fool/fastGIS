from . import app
from subprocess import check_output

@app.task
def mult(a, b):
    return a * b

@app.task
def rtest():
    ret = check_output(['mpiexec', '-np', str(2), '-hostfile',
                        '/home/truble/fastGIS/machines',
                        '/home/truble/fastGIS/mpic/mpitest'])
    return ret

