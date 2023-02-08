<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;

	class Header extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view general header">
				<div class = "agency">
					<div class = "logo"><a href = "/"></a></div>
					<div class = "info">
						<div class = "name">MyDocuments</div>
						<div class = "slogan">управляй своими документами</div>
					</div>
					<div class = "more">
						<div onclick = "$ui_menu.Open();">
							<div></div>
							<div></div>
							<div></div>
						</div>
					</div>
				</div>
				<div class = "menu">
					<div>
						<div><a>Главная</a></div>
						<div><a>О проекте</a></div>
						<div><a>Контакты</a></div>
					</div>
				</div>
			</div>
		<?php }

	}