<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;

	class Footer extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view general footer">
				<div class = "agency">
					<div class = "logo"><a href = "/"></a></div>
					<div class = "info">
						<div class = "name">MyDocuments</div>
						<div class = "slogan">управляй своими документами</div>
					</div>
					<div class = "menu">
						<div><a>Обратная связь</a></div>
						<div><a>Поддержать проект</a></div>
						<div><a>Правила сайта</a></div>
						<div><a>Политика конфиденциальности</a></div>
					</div>
				</div>
			</div>
		<?php }

	}