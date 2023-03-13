<?php

	namespace Proj\Site\Templates\General;

	use Base\Templates\View;
	use Proj\Site\Params;
	use Proj\Site\Units\General;

	class About extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render(): void { ?>
			<div class = "view general about">
				<p>Дорогой пользователь, Вы находитесь на ресурсе созданным одним человеком. Я рад, что мой ресурс приносит пользу.</p>
				<p>Я буду развивать проект и в дальнейшем. Планы по развитию такие, что сам Наполеон Бонапарт позавидовал бы. Но, конечно, без Вашего участия у меня ничего не получиться. Если Вы хотите поддержать проект, то можете кликнуть <?= General::instance()->donations->GetLink('тут', [], ['class' => 'link']); ?>, если хотите покритиковать, выразить признательность, дать дельный совет, стать моим партнёром или спонсировать на особых условиях, то пишите сюда: <?= Params::$support ?>.</p>
			</div>
		<?php }

	}