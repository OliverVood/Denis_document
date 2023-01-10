<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;
	use Proj\Site\Units\Catalogs;

	class Main extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view general main">
				<div><?= Catalogs::instance()->action_estimate->GetLink('Сметы') ?></div>
				<div><?= Catalogs::instance()->action_certificate->GetLink('Акты выполненых работ') ?></div>
				<div><?= Catalogs::instance()->action_price_list->GetLink('Прайс-листы') ?></div>
			</div>
		<?php }

	}