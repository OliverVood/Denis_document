<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;

	class Menu extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view general menu">
				<div class = "logo"><a href = "/"></a></div>
				<div class = "list">
					<a>Главная</a>
					<a>О проекте</a>
					<a>Контакты</a>
				</div>
				<div class = "more">
					<div onclick = "$ui_menu.Open();">
						<div></div>
						<div></div>
						<div></div>
					</div>
				</div>
			</div>
		<?php }

	}