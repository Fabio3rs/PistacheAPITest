# PistacheAPITest
Testing pistache.io C++ Webserver REST API with MYSQL connection

The purpose of this project is testing and study

Testing on Linux.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

src/CConfig class will expect ambient variables to work with, setup a .env file and source it.
.env file example
```
export MYSQL_HOST="tcp://127.0.0.1:3306"
export MYSQL_USER="yourmysqluser"
export MYSQL_PASSWORD="yourmysqlpassword"
export MYSQL_DATABASE="yourdatabase"

```

Compiling:
```
make -j
```

Running:
```
source .env && ./noterest
```
