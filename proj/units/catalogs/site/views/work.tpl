<?php

	namespace Proj\Site\Templates\Catalogs;

	use Base\Templates\View;

	class Work extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view catalogs work">
				<div class = "btns">
					<div><input type = "button" value = "+ Создать прайс-лист" onclick = "new Site.Catalogs.PriceList('.view.catalogs.work > .lists');"></input></div>
				</div>
				<div class = "lists"></div>
			</div>
		<?php }

	}